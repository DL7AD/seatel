#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "lwipthread.h"

#include "main.h"
#include "http.h"
#include "api.h"
#include "mde.h"
#include "imu.h"
#include "ctrl.h"
#include "debug.h"
#include "ina3221.h"
#include "ocxo.h"
#include "gps.h"

lwipthread_opts_t netif;

static const WDGConfig wdgcfg = {
    .pr =   STM32_IWDG_PR_256,
    .rlr =  STM32_IWDG_RL(0xF00)
};

static THD_WORKING_AREA(waBlinker, 256);
static THD_FUNCTION(blinker, arg)
{
    (void)arg;
    while (true)
    {
        palToggleLine(LINE_LED_READY);
        chThdSleepMilliseconds(500);
    }
}

void init(void)
{
    mde_init();
    imu_init();
    ctrl_init();
    http_init();
    api_init();
    ina3221_start();
    ocxo_init();
    gps_init();

    // Configure blinker LED
    palSetLineMode(LINE_LED_READY, PAL_MODE_OUTPUT_PUSHPULL);
    palClearLine(LINE_LED_READY);

    // Configure power pins
    palSetLineMode(LINE_PWR_LNA,     PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_PWR_EXT_5V,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_PWR_EXT_24V, PAL_MODE_OUTPUT_PUSHPULL);

    chThdCreateStatic(waBlinker, sizeof(waBlinker), LOWPRIO, blinker, NULL);
}

// Main thread
int main(void)
{
    // Startup ChibiOS
    halInit();
    chSysInit();

    // Watchdog
    wdgInit();
    wdgStart(&WDGD1, &wdgcfg);
    wdgReset(&WDGD1);

    // Startup LWIP
    lwipInit(NULL);

    // Initialize threads and pins
    init();

    while(true)
    {
        wdgReset(&WDGD1);
        chThdSleepMilliseconds(500);
    }
}
