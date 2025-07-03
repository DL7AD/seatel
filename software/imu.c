#include "imu.h"

#include "chprintf.h"
#include "debug.h"
#include <math.h>
#include <string.h>

static int16_t imu_accel_x = 0;
static int16_t imu_accel_y = 0;
static int16_t imu_accel_z = 0;

static uint16_t imu_rot_x = 0;
static uint16_t imu_rot_y = 0;
static uint16_t imu_rot_y0 = 2070;
static uint16_t imu_rot_z = 0;

static int16_t imu_el_pos = 0;
static int16_t imu_el_off = 0;
static int16_t imu_el_spd = 0;

static const SPIConfig spi_accel1 = {
    .slave = false,
    .data_cb = NULL,
    .ssport = PAL_PORT(LINE_IMU_CS1),
    .sspad = PAL_PAD(LINE_IMU_CS1),
    .cr1 = SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0 | SPI_CR1_CPHA | SPI_CR1_CPOL,
    .cr2 = 0
};

static const SPIConfig spi_accel2 = {
    .slave = false,
    .data_cb = NULL,
    .ssport = PAL_PORT(LINE_IMU_CS2),
    .sspad = PAL_PAD(LINE_IMU_CS2),
    .cr1 = SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0 | SPI_CR1_CPHA | SPI_CR1_CPOL,
    .cr2 = 0
};

static const SPIConfig spi_adc = {
    .slave = false,
    .data_cb = NULL,
    .ssport = PAL_PORT(LINE_IMU_CS3),
    .sspad = PAL_PAD(LINE_IMU_CS3),
    .cr1 = SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0 | SPI_CR1_CPHA | SPI_CR1_CPOL,
    .cr2 = 0
};

static const SPIConfig spi_mpu = {
    .slave = false,
    .data_cb = NULL,
    .ssport = PAL_PORT(LINE_IMU_MPU),
    .sspad = PAL_PAD(LINE_IMU_MPU),
    .cr1 = SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0 | SPI_CR1_CPHA | SPI_CR1_CPOL,
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


static bool imu_read_mpu9250_n(const SPIConfig* cfg, uint8_t reg, uint8_t* data, uint8_t n)
{
    if(n < 1)
        return false;

    uint8_t tx[n+1];
    uint8_t rx[n+1];
    tx[0] = reg | 0x80;

    spiStart(&SPID2, cfg);
    spiSelect(&SPID2);
    spiExchange(&SPID2, n+1, tx, rx);
    spiUnselect(&SPID2);
    spiStop(&SPID2);

    memcpy(data, &rx[1], n);

    return true;
}

static bool imu_read_mpu9250(const SPIConfig* cfg, uint8_t reg, uint8_t* data)
{
    return imu_read_mpu9250_n(cfg, reg, data, 1);
}

static bool imu_write_mpu9250(const SPIConfig* cfg, uint8_t reg, uint8_t data)
{
    uint8_t tx[2] = {reg, data};
    uint8_t rx[2];
    spiStart(&SPID2, cfg);
    spiSelect(&SPID2);
    spiExchange(&SPID2, 2, tx, rx);
    spiUnselect(&SPID2);
    spiStop(&SPID2);

    return true;
}






#define MPU9250_PWR_MGMT_1          0x6B

#define MPU9250_USER_CTRL           0x6A
#define MPU9250_I2C_MST_CTRL        0x24
#define MPU9250_I2C_MST_DELAY_CTRL  0x67
#define MPU9250_I2C_SLV4_CTRL       0x34


#define MPU9250_EXT_SENS_DATA_00    0x49
#define MPU9250_I2C_SLV0_ADDR       0x25
#define MPU9250_I2C_SLV0_REG        0x26
#define MPU9250_I2C_SLV0_CTRL       0x27
#define MPU9250_WHO_AM_I_AK8963     0x00 // should return 0x48
#define MPU9250_AK8963_ADDRESS      0x0C
#define MPU9250_AK8963_XOUT_L       0x03
#define MPU9250_AK8963_CNTL         0x0A  // Power down (0000), single-measurement (0001), self-test (1000) and Fuse ROM (1111) modes on bits 3:0
#define MPU9250_AK8963_CNTL2        0x0B  // Reset
#define MPU9250_AK8963_ASAX         0x10  // Fuse ROM x-axis sensitivity adjustment value

#define MPU9250_AK8963_M_100Hz      0x06
#define MPU9250_AK8963_MFS_16BITS   1    // 0.15 mG per LSB

#define MPU9250_I2C_SLV0_DO         0x63

static bool read_magnetometer(int16_t *mx, int16_t *my, int16_t *mz, uint8_t* whoami)
{
    imu_write_mpu9250(&spi_mpu, MPU9250_USER_CTRL, 0x20);                               // Enable I2C Master mode  
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_MST_CTRL, 0x0D);                            // I2C configuration multi-master I2C 400KHz

    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_ADDR, MPU9250_AK8963_ADDRESS | 0x80);  // Set the I2C slave address of AK8963 and set for read.
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_REG, MPU9250_WHO_AM_I_AK8963);         // I2C slave 0 register address from where to begin data transfer
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_CTRL, 0x81);                           // Enable I2C and transfer 1 byte
    chThdSleepMilliseconds(10);

    imu_read_mpu9250(&spi_mpu, MPU9250_EXT_SENS_DATA_00, whoami);                       // Read the WHO_AM_I byte
    chThdSleepMilliseconds(2);

    uint8_t raw[7];  // x/y/z gyro register data, ST2 register stored here, must read ST2 at end of data acquisition
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_ADDR, MPU9250_AK8963_ADDRESS | 0x80);    // Set the I2C slave address of AK8963 and set for read.
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_REG, MPU9250_AK8963_XOUT_L);             // I2C slave 0 register address from where to begin data transfer
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_CTRL, 0x87);                     // Enable I2C and read 7 bytes
    chThdSleepMilliseconds(2);

    imu_read_mpu9250_n(&spi_mpu, MPU9250_EXT_SENS_DATA_00, raw, 7);        // Read the x-, y-, and z-axis calibration values
    uint8_t c = raw[6]; // End data read by reading ST2 register

    if(!(c & 0x08)) { // Check if magnetic sensor overflow set, if not then report data
        *mx = ((int16_t)raw[1] << 8) | raw[0];  // Turn the MSB and LSB into a signed 16-bit value
        *my = ((int16_t)raw[3] << 8) | raw[2];  // Data stored as little Endian
        *mz = ((int16_t)raw[5] << 8) | raw[4]; 
        return true;
    }
    return false;
}

static THD_WORKING_AREA(waIMU, 4096);
static THD_FUNCTION(imu, arg)
{
    (void)arg;

    uint16_t miso;
    int32_t accu = 0;
    uint8_t cntr = 0;
    //uint8_t cntr_print = 0;
    //uint32_t ms;

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
        accu += -(imu_rot_y-imu_rot_y0)*11;
        cntr += 1;
        if(cntr >= 5) {
            imu_el_spd = accu/cntr;
            accu = cntr = 0;
        }

//        // Reading values from MPU9250 Magnetometer
//        int16_t mx, my, mz;
//        uint8_t whoami = 0;
//        bool success = true;//read_magnetometer(&mx, &my, &mz, &whoami);
//
//        if(cntr_print++ % 100 == 0)
//        {
//            char buf[128];
//            uint32_t delta = TIME_I2MS(chVTGetSystemTimeX()) - ms;
//            ms = TIME_I2MS(chVTGetSystemTimeX());
//            chsnprintf(buf, sizeof(buf), "[%.3f] loop*100 delta=%d\n", ms/1000.0, delta);
//            debug_print(buf);
//        }
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

    // Wake up MPU9250
    imu_write_mpu9250(&spi_mpu, MPU9250_PWR_MGMT_1, 0x00);
    chThdSleepMilliseconds(100);

    imu_write_mpu9250(&spi_mpu, MPU9250_USER_CTRL, 0x20);          // Enable I2C Master mode  
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_MST_CTRL, 0x1D);       // I2C configuration STOP after each transaction, master I2C bus at 400 KHz
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_MST_DELAY_CTRL, 0x81); // Use blocking data retreival and enable delay for mag sample rate mismatch
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV4_CTRL, 0x01);      // Delay mag data retrieval to once every other accel/gyro data sample



    uint8_t mscale = MPU9250_AK8963_MFS_16BITS;
    uint8_t mmode = MPU9250_AK8963_M_100Hz;
    uint8_t _mmode;
    float magCalibration[3];
    float _magCalibration[3];

    // First extract the factory calibration for each magnetometer axis
    uint8_t rawData[3];  // x/y/z gyro calibration data stored here

    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_ADDR, MPU9250_AK8963_ADDRESS);         // Set the I2C slave address of AK8963 and set for write.
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_REG, MPU9250_AK8963_CNTL2);            // I2C slave 0 register address from where to begin data transfer
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_DO, 0x01);                             // Reset AK8963
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_CTRL, 0x81);                           // Enable I2C and write 1 byte
    chThdSleepMilliseconds(50);
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_ADDR, MPU9250_AK8963_ADDRESS);         // Set the I2C slave address of AK8963 and set for write.
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_REG, MPU9250_AK8963_CNTL);             // I2C slave 0 register address from where to begin data transfer
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_DO, 0x00);                             // Power down magnetometer  
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_CTRL, 0x81);                           // Enable I2C and write 1 byte
    chThdSleepMilliseconds(50);
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_ADDR, MPU9250_AK8963_ADDRESS);         // Set the I2C slave address of AK8963 and set for write.
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_REG, MPU9250_AK8963_CNTL);             // I2C slave 0 register address from where to begin data transfer
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_DO, 0x0F);                             // Enter fuze mode
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_CTRL, 0x81);                           // Enable I2C and write 1 byte
    chThdSleepMilliseconds(50);

    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_ADDR, MPU9250_AK8963_ADDRESS | 0x80);  // Set the I2C slave address of AK8963 and set for read.
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_REG, MPU9250_AK8963_ASAX);             // I2C slave 0 register address from where to begin data transfer
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_CTRL, 0x83);                           // Enable I2C and read 3 bytes
    chThdSleepMilliseconds(50);
    imu_read_mpu9250_n(&spi_mpu, MPU9250_EXT_SENS_DATA_00, &rawData[0], 3);             // Read the x-, y-, and z-axis calibration values
    magCalibration[0] =  (float)(rawData[0] - 128)/256.0f + 1.0f;                       // Return x-axis sensitivity adjustment values, etc.
    magCalibration[1] =  (float)(rawData[1] - 128)/256.0f + 1.0f;  
    magCalibration[2] =  (float)(rawData[2] - 128)/256.0f + 1.0f; 
    _magCalibration[0] = magCalibration[0];
    _magCalibration[1] = magCalibration[1];
    _magCalibration[2] = magCalibration[2];
    (void)_magCalibration;
    _mmode = mmode;
    (void)_mmode;

    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_ADDR, MPU9250_AK8963_ADDRESS);         // Set the I2C slave address of AK8963 and set for write.
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_REG, MPU9250_AK8963_CNTL);             // I2C slave 0 register address from where to begin data transfer
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_DO, 0x00);                             // Power down magnetometer  
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_CTRL, 0x81);                           // Enable I2C and transfer 1 byte
    chThdSleepMilliseconds(50);

    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_ADDR, MPU9250_AK8963_ADDRESS);         // Set the I2C slave address of AK8963 and set for write.
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_REG, MPU9250_AK8963_CNTL);             // I2C slave 0 register address from where to begin data transfer 
    // Configure the magnetometer for continuous read and highest resolution
    // set mscale bit 4 to 1 (0) to enable 16 (14) bit resolution in CNTL register,
    // and enable continuous mode data acquisition Mmode (bits [3:0]), 0010 for 8 Hz and 0110 for 100 Hz sample rates
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_DO, mscale << 4 | mmode);              // Set magnetometer data resolution and sample ODR
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_CTRL, 0x81);                           // Enable I2C and transfer 1 byte
    chThdSleepMilliseconds(50);
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_ADDR, MPU9250_AK8963_ADDRESS | 0x80);  // Set the I2C slave address of AK8963 and set for read.
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_REG, MPU9250_AK8963_CNTL);             // I2C slave 0 register address from where to begin data transfer
    imu_write_mpu9250(&spi_mpu, MPU9250_I2C_SLV0_CTRL, 0x81);                           // Enable I2C and transfer 1 byte
    chThdSleepMilliseconds(50);












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

void imu_calibrate(void)
{
    int32_t accu = 0;
    for(uint8_t i=0; i<100; i++)
    {
        accu += imu_rot_y;
        chThdSleepMilliseconds(10);
    }
    imu_rot_y0 = accu/100;
}

int16_t imu_get_el_off(void)
{
    return imu_el_off;
}

void imu_set_el_off(int16_t off)
{
    imu_el_off = off;
}
