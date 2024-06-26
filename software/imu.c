#include "imu.h"

#include "chprintf.h"
#include "debug.h"
#include <math.h>

static int16_t imu_accel_x = 0;
static int16_t imu_accel_y = 0;
static int16_t imu_accel_z = 0;

static uint16_t imu_rot_x = 0;
static uint16_t imu_rot_y = 0;
static uint16_t imu_rot_z = 0;

static int16_t imu_el_pos = 0;
static int16_t imu_el_spd = 0;

static const SPIConfig spi_accel1 = {
    .slave = false,
    .data_cb = NULL,
    .ssport = PAL_PORT(LINE_IMU_CS1),
    .sspad = PAL_PAD(LINE_IMU_CS1),
    .cr1 = SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2 | SPI_CR1_CPHA | SPI_CR1_CPOL,
    .cr2 = 0
};

static const SPIConfig spi_accel2 = {
    .slave = false,
    .data_cb = NULL,
    .ssport = PAL_PORT(LINE_IMU_CS2),
    .sspad = PAL_PAD(LINE_IMU_CS2),
    .cr1 = SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2 | SPI_CR1_CPHA | SPI_CR1_CPOL,
    .cr2 = 0
};

static const SPIConfig spi_adc = {
    .slave = false,
    .data_cb = NULL,
    .ssport = PAL_PORT(LINE_IMU_CS3),
    .sspad = PAL_PAD(LINE_IMU_CS3),
    .cr1 = SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2 | SPI_CR1_CPHA | SPI_CR1_CPOL,
    .cr2 = 0
};

static const SPIConfig spi_mpu = {
    .slave = false,
    .data_cb = NULL,
    .ssport = PAL_PORT(LINE_IMU_MPU),
    .sspad = PAL_PAD(LINE_IMU_MPU),
    .cr1 = SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2 | SPI_CR1_CPHA | SPI_CR1_CPOL,
    .cr2 = 0
};

static bool imu_exchange(const SPIConfig* cfg, uint16_t mosi, uint16_t* miso)
{
    uint8_t tx[2] = {mosi >> 8, mosi};
    uint8_t rx[2];
    spiStart(&SPID2, cfg);
    spiSelect(&SPID2);
    spiExchange(&SPID2, 2, tx, rx);
    spiUnselect(&SPID2);
    spiStop(&SPID2);

    if(miso != NULL)
        *miso = (rx[0] << 8) | rx[1];

    return true;
}

static bool imu_exchange_88(const SPIConfig* cfg, uint8_t mosi, uint8_t* miso)
{
    uint8_t tx[2] = {mosi, 0x00};
    uint8_t rx[2];
    spiStart(&SPID2, cfg);
    spiSelect(&SPID2);
    spiExchange(&SPID2, 2, tx, rx);
    spiUnselect(&SPID2);
    spiStop(&SPID2);

    if(miso != NULL)
        *miso = rx[1];

    return true;
}

static void read_magnetometer(int16_t *mx, int16_t *my, int16_t *mz)
{
    uint8_t mxl, mxh, myl, myh, mzl, mzh;

    // Read magnetometer registers
    imu_exchange_88(&spi_mpu, 0x03 | 0x80, &mxl);
    imu_exchange_88(&spi_mpu, 0x04 | 0x80, &mxh);
    imu_exchange_88(&spi_mpu, 0x05 | 0x80, &myl);
    imu_exchange_88(&spi_mpu, 0x06 | 0x80, &myh);
    imu_exchange_88(&spi_mpu, 0x07 | 0x80, &mzl);
    imu_exchange_88(&spi_mpu, 0x08 | 0x80, &mzh);

    // Combine high and low bytes
    *mx = (int16_t)(mxh << 8 | mxl);
    *my = (int16_t)(myh << 8 | myl);
    *mz = (int16_t)(mzh << 8 | mzl);
}

static THD_WORKING_AREA(waIMU, 4096);
static THD_FUNCTION(imu, arg)
{
    (void)arg;

    uint16_t miso;
    int32_t accu = 0;
    uint8_t cntr = 0;

    while(true)
    {
        // Reading values from ADIS16209
        imu_exchange(&spi_accel1, 0x0400, &miso);
        chThdSleepMicroseconds(50);
        imu_exchange(&spi_accel1, 0x0000, &miso);
        imu_accel_z = -((int16_t)((miso & 0x3FFF) << 2) / 4);
        chThdSleepMicroseconds(50);

        imu_exchange(&spi_accel1, 0x0600, &miso);
        chThdSleepMicroseconds(50);
        imu_exchange(&spi_accel1, 0x0000, &miso);
        imu_accel_x = (int16_t)((miso & 0x3FFF) << 2) / 4;
        chThdSleepMicroseconds(10);

        imu_exchange(&spi_accel2, 0x0600, &miso);
        chThdSleepMicroseconds(50);
        imu_exchange(&spi_accel2, 0x0000, &miso);
        imu_accel_y = -((int16_t)((miso & 0x3FFF) << 2) / 4);
        chThdSleepMicroseconds(10);

        // Reading values from ADC124S101
        imu_exchange(&spi_adc, 0x0000, &miso);
        imu_rot_x = miso & 0x0FFF;
        chThdSleepMicroseconds(10);

        imu_exchange(&spi_adc, 0x0800, &miso);
        imu_rot_y = miso & 0x0FFF;
        chThdSleepMicroseconds(10);

        imu_exchange(&spi_adc, 0x1000, &miso);
        imu_rot_z = miso & 0x0FFF;
        chThdSleepMicroseconds(10);

        // Calculating elevation parameters
        imu_el_pos = atan(-(float)imu_accel_z/(float)imu_accel_x)*10430;
        if(imu_accel_x > 0) imu_el_pos += 32768;

        // FIXME: Following calculation isn't 100% correct. the imu_rot_x needs to be inserted too.
        accu += -(imu_rot_y-2070)*11;
        cntr += 1;
        if(cntr >= 5) {
            imu_el_spd = accu/cntr;
            accu = cntr = 0;
        }

//        int16_t mx, my, mz;
//        read_magnetometer(&mx, &my, &mz);
//
//        char buf[64];
//        uint32_t ms = TIME_I2MS(chVTGetSystemTimeX());
//        chsnprintf(buf, sizeof(buf), "[%.3f] mx=%d my=%d mz=%d\n",
//            ms/1000.0, mx, my, mz);
//        debug_print(buf);
//        chThdSleepMilliseconds(300);

        chThdSleepMilliseconds(3);
    }
}

void imu_init(void)
{
    // Configure IMU pins
    palSetLineMode(LINE_IMU_MOSI, PAL_MODE_ALTERNATE(5));
    palSetLineMode(LINE_IMU_MISO, PAL_MODE_ALTERNATE(5));
    palSetLineMode(LINE_IMU_SCK,  PAL_MODE_ALTERNATE(5));
    palSetLineMode(LINE_IMU_CS1,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_IMU_CS2,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_IMU_CS3,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_IMU_MPU,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_IMU_EN,   PAL_MODE_OUTPUT_PUSHPULL);
    palSetLine(LINE_IMU_CS1);
    palSetLine(LINE_IMU_CS2);
    palSetLine(LINE_IMU_CS3);
    palSetLine(LINE_IMU_MPU);
    palSetLine(LINE_IMU_EN);

    //imu_exchange(&spi_mpu, 0x6B00, NULL);

    imu_exchange(&spi_mpu, 0x6B00, NULL); // Write to PWR_MGMT_1, set to zero (wakes up the MPU-9250)
    chThdSleepMilliseconds(100);

    // Set the I2C master mode to pass-through for the AK8963
    imu_exchange(&spi_mpu, 0x3702, NULL); // INT_PIN_CFG register: set bit 1 to enable I2C bypass
    chThdSleepMilliseconds(100);

    // Power down magnetometer
    imu_exchange(&spi_mpu, 0x0A00, NULL);
    chThdSleepMilliseconds(100);

    // Enter Fuse ROM access mode
    imu_exchange(&spi_mpu, 0x0A0F, NULL);
    chThdSleepMilliseconds(100);

    // Power down magnetometer
    imu_exchange(&spi_mpu, 0x0A00, NULL);
    chThdSleepMilliseconds(100);

    // Set magnetometer to continuous measurement mode
    imu_exchange(&spi_mpu, 0x0A06, NULL);
    chThdSleepMilliseconds(100);

    chThdCreateStatic(waIMU, sizeof(waIMU), HIGHPRIO, imu, NULL);
}

int16_t imu_get_accel_x(void) {
    return imu_accel_x;
}

int16_t imu_get_accel_y(void) {
    return imu_accel_y;
}

int16_t imu_get_accel_z(void) {
    return imu_accel_z;
}

uint16_t imu_get_rot_x(void) {
    return imu_rot_x;
}

uint16_t imu_get_rot_y(void) {
    return imu_rot_y;
}

uint16_t imu_get_rot_z(void) {
    return imu_rot_z;
}

int16_t imu_get_el_pos(void) {
    return imu_el_pos;
}

int16_t imu_get_el_spd(void) {
    return imu_el_spd;
}
