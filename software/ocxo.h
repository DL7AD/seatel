#ifndef _OCXO_H_
#define _OCXO_H_

#include "ch.h"
#include "hal.h"

#define LINE_OCXO_10M   PAL_LINE(GPIOA, 15)
#define LINE_OCXO_20M   PAL_LINE(GPIOA, 0)
#define LINE_OCXO_DAC   PAL_LINE(GPIOA, 4)
#define LINE_GPS_1PPS   PAL_LINE(GPIOA, 3)
#define LINE_LED_1PPS   PAL_LINE(GPIOE, 9)

void ocxo_init(void);

systime_t ocxo_get_last_pulse(void);
int32_t ocxo_get_cntr(void);
uint16_t ocxo_get_dac_val(void);

#endif
