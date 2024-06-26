#include "mde.h"

static int8_t motor_az = 0;
static int8_t motor_el = 0;
static int8_t motor_sk = 0;

static uint16_t enc_az = 0;
static int16_t enc_az_speed = 0;

static bool power_up; // Command flag to power up MDE
static bool power_dn; // Command flag to power down MDE
static bool is_powered_up;

static const SPIConfig spi_mde = {
    .slave = false,
    .data_cb = NULL,
    .ssport = PAL_PORT(LINE_MDE_CS),
    .sspad = PAL_PAD(LINE_MDE_CS),
    .cr1 = SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2 | SPI_CR1_CPHA,
    .cr2 = 0
};

static uint8_t bit_count(uint16_t n)
{
    uint8_t cntr = 0;
    while(n) {
        cntr += n % 2;
        n >>= 1;
    }
    return cntr;
}

static bool mde_exchange(uint16_t mosi, uint16_t* miso)
{
    uint8_t tx[2] = {mosi >> 8, mosi};
    uint8_t rx[2];
    spiStart(&SPID3, &spi_mde);
    spiSelect(&SPID3);
    spiExchange(&SPID3, 2, tx, rx);
    spiUnselect(&SPID3);

    if(miso != NULL)
        *miso = (rx[0] << 8) | rx[1];

    return true;
}

static uint16_t mde_cmd_set_mot_trq(uint8_t motor, int8_t speed)
{
    //              Command           Motor                 Speed
    uint16_t cmd = (0b1110 << 12) | ((motor & 0x7) << 9) | ((uint8_t)speed << 1);
    cmd |= !(bit_count(cmd) & 0x1); // CRC
    return cmd;
}

static THD_WORKING_AREA(waMDE, 4096);
static THD_FUNCTION(mde, arg)
{
    (void)arg;

    uint16_t miso;
    systime_t old_t;
    uint16_t old_x;

    while(true)
    {
        if(power_dn && is_powered_up)
        {
            palClearLine(LINE_MDE_PWR);
            chThdSleepMilliseconds(1000);
            power_dn = false;
            is_powered_up = false;
        }

        if(power_up && !is_powered_up)
        {
            palSetLine(LINE_MDE_PWR);
            chThdSleepMilliseconds(5000);

            mde_exchange(0x5ba5, NULL); // 26.7533859 init
            mde_exchange(0xf4ff, NULL); // 26.7534515 init
            mde_exchange(0xf4ff, NULL); // 26.7535157 init
            mde_exchange(0xa8ff, NULL); // 26.7536471 init
            mde_exchange(0xa9fe, NULL); // 26.7537115 init
            mde_exchange(0xa9fd, NULL); // 26.7537753 init
            mde_exchange(0xa8fc, NULL); // 26.7538396 init
            mde_exchange(0xa9fb, NULL); // 26.7539053 init
            mde_exchange(0xa8fa, NULL); // 26.7539707 init
            mde_exchange(0xa8f9, NULL); // 26.754035  init
            mde_exchange(0xa9f8, NULL); // 26.7540988 init
            mde_exchange(0xa9f7, NULL); // 26.7541631 init
            mde_exchange(0xa8f6, NULL); // 26.7542273 init
            mde_exchange(0xa8f5, NULL); // 26.7542936 init
            mde_exchange(0xa9f4, NULL); // 26.754358  init
            mde_exchange(0xa8f3, NULL); // 26.7544223 init
            mde_exchange(0xa9f2, NULL); // 26.7544866 init
            mde_exchange(0xa9f1, NULL); // 26.7545509 init
            chThdSleepMilliseconds(100); // ex 14300

            mde_exchange(0xa45a, NULL); // 41.1235303 init
            mde_exchange(0xa45a, NULL); // 41.1235952 init
            chThdSleepMilliseconds(100);

            mde_exchange(0xfbff, NULL); // 41.2336385
            mde_exchange(0xd9f9, NULL); // 41.3435124 init
            mde_exchange(0xd7ef, NULL); // 41.3435778 init
            mde_exchange(0xdcff, NULL); // 41.3436424 init
            mde_exchange(0xdaff, NULL); // 41.3437068 init
            mde_exchange(0xfb77, NULL); // 41.3438994
            mde_exchange(0xfa76, NULL); // 41.3439642 init
            mde_exchange(0xfafb, NULL); // 41.3441579 init

            mde_exchange(0xfdff, NULL); // 41.3453731 0xfd 0xfe 0xff 0xff
            mde_exchange(0xfcfe, NULL); // 41.3454375 0xfc 0xbf 0xfe 0xff

            power_up = false;
            is_powered_up = true;
        }

        if(is_powered_up)
        {
            // Get encoder reading
            mde_exchange(0xFEFF, &miso);
            mde_exchange(0xFEFF, &miso);
            //chThdSleepMilliseconds(50);
            mde_exchange(0xFEFF, &miso);
            mde_exchange(0xFEFF, &miso);
            mde_exchange(0xFDFF, &miso);
            bool status_fc = mde_exchange(0xFCFE, &miso);
            uint8_t fc = miso & 0xFF;
            bool status_fb = mde_exchange(0xFBFF, &miso);
            uint8_t fb = miso & 0xFF;
            if(status_fb && status_fc)
            {
                enc_az = ~((fc << 8) | fb);

                double dt = (double)(chVTGetSystemTimeX()-old_t)/CH_CFG_ST_FREQUENCY;
                int16_t dx = (int16_t)enc_az-(int16_t)old_x;
                enc_az_speed = dx/dt;
                old_x = enc_az;
                old_t = chVTGetSystemTimeX();
            }

            // Set motor speeds
            mde_exchange(mde_cmd_set_mot_trq(MOTOR_AZ, motor_az), NULL);
            mde_exchange(mde_cmd_set_mot_trq(MOTOR_EL, motor_el), NULL);
            mde_exchange(mde_cmd_set_mot_trq(MOTOR_SK, motor_sk), NULL);
        }

        chThdSleepMilliseconds(3);
    }
}

void mde_init(void)
{
    // Configure MDE pins
    palSetLineMode(LINE_MDE_MOSI, PAL_MODE_ALTERNATE(6));
    palSetLineMode(LINE_MDE_MISO, PAL_MODE_ALTERNATE(6));
    palSetLineMode(LINE_MDE_SCK,  PAL_MODE_ALTERNATE(6));
    palSetLineMode(LINE_MDE_CS,   PAL_MODE_OUTPUT_PUSHPULL);
    palSetLine(LINE_MDE_CS);

    palSetLineMode(LINE_MDE_PWR, PAL_MODE_OUTPUT_PUSHPULL);
    palClearLine(LINE_MDE_PWR);

    chThdCreateStatic(waMDE, sizeof(waMDE), HIGHPRIO, mde, NULL);
}

void mde_power_up(void)
{
    power_up = true;
}

void mde_power_down(void)
{
    power_dn = true;
}

uint16_t mde_get_az_enc_pos(void)
{
    return enc_az;
}

int16_t mde_get_az_enc_spd(void)
{
    return enc_az_speed;
}

int8_t mde_get_trq_az(void) {
    return motor_az;
}

void mde_set_trq_az(int8_t trq) {
    motor_az = trq;
}

int8_t mde_get_trq_el(void) {
    return motor_el;
}

void mde_set_trq_el(int8_t trq) {
    motor_el = trq;
}

int8_t mde_get_trq_sk(void) {
    return motor_sk;
}

void mde_set_trq_sk(int8_t trq) {
    motor_sk = trq;
}
