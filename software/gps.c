#include "gps.h"

#include "ch.h"
#include "hal.h"
#include "ocxo.h"
#include "debug.h"
#include <string.h>
#include <stdlib.h>

static const SerialConfig gps_cfg = {
    9600,
    0,
    0,
    0
};

static uint32_t m_date;
static uint32_t m_time;
static float    m_lat;
static float    m_lon;
static int16_t  m_alt;
static uint8_t  m_sats;
static uint8_t  m_sats_sol;

void gps_parse(char* str)
{
    // Example GPGGA message
    // 000000000011111111112222222222333333333344444444445555555555666666
    // 012345678901234567890123456789012345678901234567890123456789012345
    // $GPGGA,181010,5224.7214,N,01323.6669,E,2,08,1.1,13.8,M,42.0,M,,*71
    if(!strncmp(str, "$GPGGA", 6))
    {
        m_time     = atoi(&str[7]);
        m_lat      = (atoi(&str[14])/100 + (atoi(&str[16]) + atoi(&str[19]) / 10000.0) / 60.0) * (str[24]=='N' ? 1 : -1);
        m_lon      = (atoi(&str[26])/100 + (atoi(&str[29]) + atoi(&str[32]) / 10000.0) / 60.0) * (str[37]=='E' ? 1 : -1);
        m_sats_sol = atoi(&str[41]);
        m_alt      = atoi(&str[48]);
    }
    // Example PGRMF message
    // 000000000011111111112222222222333333333344444444445555555555666666
    // 012345678901234567890123456789012345678901234567890123456789012345
    // $PGRMF,142,518553,180502,000215,18,5230.0000,N,01329.9932,E,A,2,0,218,3,1*16
    if(!strncmp(str, "$PGRMF", 6))
    {
        m_date     = atoi(&str[18]);
    }
}

static THD_WORKING_AREA(waGPS, 2048);
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
            gps_parse(buf);
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

void gps_init(void)
{
    // Configure GPS pins
    palSetLineMode(LINE_GPS_TXD, PAL_MODE_ALTERNATE(7));
    palSetLineMode(LINE_GPS_RXD, PAL_MODE_ALTERNATE(7));
    sdStart(&SD3, &gps_cfg);

    chThdCreateStatic(waGPS, sizeof(waGPS), HIGHPRIO, gps, NULL);
}

void get_gps_data(uint32_t* date, uint32_t* time, float* lat, float* lon, int16_t* alt, uint8_t* sats, uint8_t* sats_sol, bool* pulse)
{
    *date     = m_date;
    *time     = m_time;
    *lat      = m_lat;
    *lon      = m_lon;
    *alt      = m_alt;
    *sats     = m_sats;
    *sats_sol = m_sats_sol;
    uint32_t td = TIME_I2MS(chVTGetSystemTimeX()-ocxo_get_last_pulse());
    *pulse    = td <= 200;
}
