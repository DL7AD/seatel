#ifndef _OCXO_H_
#define _OCXO_H_

#include "ch.h"
#include "hal.h"

#define LINE_OCXO_10M   PAL_LINE(GPIOA, 15)
#define LINE_OCXO_20M   PAL_LINE(GPIOA, 0)
#define LINE_OCXO_DAC   PAL_LINE(GPIOA, 4)
#define LINE_GPS_1PPS   PAL_LINE(GPIOA, 3)

#define LINE_GPS_TXD    PAL_LINE(GPIOD, 8)
#define LINE_GPS_RXD    PAL_LINE(GPIOD, 9)

void ocxo_init(void);

#endif
