#ifndef _GPS_H_
#define _GPS_H_

#include "ch.h"
#include "hal.h"

#define LINE_GPS_TXD    PAL_LINE(GPIOD, 8)
#define LINE_GPS_RXD    PAL_LINE(GPIOD, 9)

void gps_init(void);
void get_gps_data(uint32_t* date, uint32_t* time, float* lat, float* lon, int16_t* alt, uint8_t* sats, uint8_t* sats_sol, bool* pulse);

#endif
