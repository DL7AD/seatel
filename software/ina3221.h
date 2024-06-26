#ifndef _INA3221_H_
#define _INA3221_H_

#include "ch.h"
#include "hal.h"

#define MSG_ERROR (msg_t)-3

typedef int32_t mon_reading_t;
typedef uint8_t mon_unit_t;

typedef enum monPort {
    MON_NO_PORT = 0,
    MON_PORT_1,
    MON_PORT_2,
    MON_PORT_3,
    MON_PORT_4,
    MON_PORT_5,
    MON_PORT_6,
} mon_port_t;

typedef enum {
    MON_NMVOLT,
    MON_NMWATT,
} mon_compute_t;

typedef struct monSrc {
    mon_port_t    ports;
    mon_compute_t compute;
} mon_source_t;

typedef struct pwrDevCfg{
    I2CDriver*       drv;
    i2caddr_t        addr;
    const I2CConfig* cfg;
} pwr_unit_cfg_t;

typedef enum {
  MON_DEV_IDLE,
  MON_DEV_OK,
  MON_DEV_FAULT,
  MON_DEV_ERROR,
  MON_DEV_UNEQUIPPED,
  MON_DEV_UNSUPPORTED
} dev_status_t;

bool ina3221_isAvailable(const pwr_unit_cfg_t* pcfg);
bool ina3221_start(void);
msg_t ina3221_get_current_reading(const mon_source_t *source, mon_reading_t *mrp);

#endif
