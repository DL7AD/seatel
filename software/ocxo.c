#include "ocxo.h"

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "debug.h"

static const GPTConfig gpt_cfg = {
    .frequency = 1000000
};

static const DACConfig dac_cfg = {
    .init     = 2047U,
    .datamode = DAC_DHRM_12BIT_RIGHT,
    .cr       = 0
};

static const SerialConfig gps_cfg = {
    9600,
    0,
    0,
    0
};

int32_t last_cnt;

static THD_WORKING_AREA(waOCXO, 1024);
static THD_FUNCTION(ocxo, arg)
{
    (void)arg;

    // Frequency counter
    gptStart(&GPTD2, &gpt_cfg);
    GPTD2.tim->SMCR = TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0 | TIM_SMCR_TS_2 | TIM_SMCR_TS_1 | TIM_SMCR_TS_0;
    GPTD2.tim->PSC = 0;
    gptStartContinuous(&GPTD2, 0xFFFFFFFF); // Start with maximum period

    while(true)
    {
        if(last_cnt != -1)
        {
            char buf[64];
            uint32_t ms = TIME_I2MS(chVTGetSystemTimeX());
            chsnprintf(buf, sizeof(buf), "[%.3f] cntr=%d\n",
                ms/1000.0, last_cnt);
            debug_print(buf);
            last_cnt = -1;
        }

        //dacPutChannelX(&DACD1, 0, i++);

        chThdSleepMilliseconds(100);
    }
}

static THD_WORKING_AREA(waGPS, 1024);
static THD_FUNCTION(gps, arg)
{
    (void)arg;

    char buf[128];
    size_t idx = 0;

    while (true)
    {
        char c = sdGet(&SD3);
        if(!c) {
            chThdSleepMilliseconds(50);
            continue;
        }
        if (c == '\n' || c == '\r') {
            buf[idx] = '\0';
            debug_print(buf);
            idx = 0;
        } else {
            if (idx < sizeof(buf)-1) {
                buf[idx++] = c;
            } else {
                idx = 0;
            }
        }
    }
}

static void exti_cb(void *arg) {
    (void)arg;

    last_cnt = GPTD2.tim->CNT;
    GPTD2.tim->CNT = 0;
}

void ocxo_init(void)
{
    // Configure OCXO pins
    palSetLineMode(LINE_OCXO_10M, PAL_MODE_UNCONNECTED);
    palSetLineMode(LINE_OCXO_20M, PAL_MODE_ALTERNATE(1));

    palSetLineMode(LINE_GPS_1PPS, PAL_MODE_INPUT);
    palEnableLineEvent(LINE_GPS_1PPS, PAL_EVENT_MODE_RISING_EDGE);
    palSetLineCallback(LINE_GPS_1PPS, exti_cb, NULL);

    palSetLineMode(LINE_OCXO_DAC, PAL_MODE_INPUT_ANALOG);
    dacStart(&DACD1, &dac_cfg);

    palSetLineMode(LINE_GPS_TXD, PAL_MODE_ALTERNATE(7));
    palSetLineMode(LINE_GPS_RXD, PAL_MODE_ALTERNATE(7));
    sdStart(&SD3, &gps_cfg);

    chThdCreateStatic(waGPS, sizeof(waGPS), HIGHPRIO, gps, NULL);
    chThdCreateStatic(waOCXO, sizeof(waOCXO), HIGHPRIO, ocxo, NULL);
}
