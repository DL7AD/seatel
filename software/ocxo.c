#include "ocxo.h"

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "debug.h"

static const GPTConfig gpt_cfg = {
    .frequency = 1000000
};

static const DACConfig dac_cfg = {
    .init     = 2050U,
    .datamode = DAC_DHRM_12BIT_RIGHT,
    .cr       = 0
};

static int32_t ocxo_cntr[3] = {0,1,2};
static uint32_t cntr_i = 0;
static int32_t out_ocxo_cntr;
static systime_t last_pulse;
static uint16_t dac_val = 2050;

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
        if(ocxo_cntr[0] == ocxo_cntr[1] && ocxo_cntr[1] == ocxo_cntr[2])
        {
            out_ocxo_cntr = ocxo_cntr[0];
            ocxo_cntr[0] = -1;

            char buf[64];
            uint32_t ms = TIME_I2MS(chVTGetSystemTimeX());
            chsnprintf(buf, sizeof(buf), "[%.3f] cntr=%d\n",
                ms/1000.0, out_ocxo_cntr);
            debug_print(buf);

            if(out_ocxo_cntr > 20000001) {
                dac_val -= 10;
            } else if(out_ocxo_cntr < 19999999) {
                dac_val += 10;
            }
            dacPutChannelX(&DACD1, 0, dac_val);
        }
        if(TIME_I2MS(chVTGetSystemTimeX()-last_pulse) > 100)
        {
            palClearLine(LINE_LED_1PPS);
        }

        chThdSleepMilliseconds(10);
    }
}

static void exti_cb(void *arg) {
    (void)arg;

    ocxo_cntr[cntr_i++ % 3] = GPTD2.tim->CNT;
    GPTD2.tim->CNT = 0;
    last_pulse = chVTGetSystemTimeX();

    palSetLine(LINE_LED_1PPS);
}

void ocxo_init(void)
{
    // Configure OCXO pins
    palSetLineMode(LINE_OCXO_10M, PAL_MODE_UNCONNECTED);
    palSetLineMode(LINE_OCXO_20M, PAL_MODE_ALTERNATE(1));

    palSetLineMode(LINE_GPS_1PPS, PAL_MODE_INPUT_PULLDOWN);
    palEnableLineEvent(LINE_GPS_1PPS, PAL_EVENT_MODE_RISING_EDGE);
    palSetLineCallback(LINE_GPS_1PPS, exti_cb, NULL);

    palSetLineMode(LINE_LED_1PPS, PAL_MODE_OUTPUT_PUSHPULL);
    palClearLine(LINE_LED_1PPS);

    palSetLineMode(LINE_OCXO_DAC, PAL_MODE_INPUT_ANALOG);
    dacStart(&DACD1, &dac_cfg);

    chThdCreateStatic(waOCXO, sizeof(waOCXO), HIGHPRIO, ocxo, NULL);
}

systime_t ocxo_get_last_pulse(void)
{
    return last_pulse;
}

int32_t ocxo_get_cntr(void)
{
    return out_ocxo_cntr;
}

uint16_t ocxo_get_dac_val(void)
{
    return dac_val;
}
