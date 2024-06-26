/*
    ChibiOS/RT - Copyright (C) 2006-2013 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>

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
        palToggleLine(LINE_READY);
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

    // Configure state LEDs
    palSetLineMode(LINE_CONNECTED, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_READY, PAL_MODE_OUTPUT_PUSHPULL);
    palClearLine(LINE_CONNECTED);
    palClearLine(LINE_READY);

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
