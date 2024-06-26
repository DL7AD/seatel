
#include "ina3221.h"


/*===========================================================================*/
/* Module pre-compile settings.                                              */
/*===========================================================================*/

#if !defined(INA3221_OB_ADDRESS)
#define INA3221_OB_ADDRESS               0x40
#endif

#if !defined(INA3221_CH1_RSENSE)
#define INA3221_CH1_RSENSE            0.01      /* current sense in ohms */
#endif
#if !defined(INA3221_CH2_RSENSE)
#define INA3221_CH2_RSENSE            0.01      /* current sense in ohms */
#endif
#if !defined(INA3221_CH3_RSENSE)
#define INA3221_CH3_RSENSE            0.01      /* current sense in ohms */
#endif
#if !defined(INA3221_CH4_RSENSE)
#define INA3221_CH4_RSENSE            0.01      /* current sense in ohms */
#endif
#if !defined(INA3221_CH5_RSENSE)
#define INA3221_CH5_RSENSE            0.01      /* current sense in ohms */
#endif
#if !defined(INA3221_CH6_RSENSE)
#define INA3221_CH6_RSENSE            0.01      /* current sense in ohms */
#endif

/*===========================================================================*/
/* Module local definitions.                                                 */
/*===========================================================================*/

#define INA3221_CONFIGURATION         0x00
#define INA3221_CHAN1_REGS            0x01
#define INA3221_CHAN1_SHUNT_VOLTAGE   INA3221_CHAN1_REGS
#define INA3221_CHAN1_BUS_VOLTAGE     0x02
#define INA3221_CHAN2_REGS            0x03
#define INA3221_CHAN2_SHUNT_VOLTAGE   INA3221_CHAN2_REGS
#define INA3221_CHAN2_BUS_VOLTAGE     0x04
#define INA3221_CHAN3_REGS            0x05
#define INA3221_CHAN3_SHUNT_VOLTAGE   INA3221_CHAN3_REGS
#define INA3221_CHAN3_BUS_VOLTAGE     0x06


#define INA3221_MANUFACTURER_ID       0xFE
#define INA3221_DIE_ID                0xFF

/*===========================================================================*/
/* Module local types.                                                       */
/*===========================================================================*/

/* Data reference for ths instance.*/
//static const pwr_unit_cfg_t *pcfg40 = NULL;
//static const pwr_unit_cfg_t *pcfg41 = NULL;

/* Register address.*/
typedef uint8_t ina3221_rad_t;

/* Raw register reference.*/
typedef uint16_t ina3221_rreg_t;

/* Signed register reference.*/
typedef int16_t  ina3221_vreg_t;

/* Channel voltage register set.*/
typedef struct {
  ina3221_vreg_t shunt;
  ina3221_vreg_t bus;
} ina3221_chan_t;

/* Channel calculation object.*/
typedef struct {
  mon_reading_t   bus_volt;
  mon_reading_t   shunt_volt;
} ina3221_mon_t;

/*===========================================================================*/
/* Module local data.                                                        */
/*===========================================================================*/

static dev_status_t error = MON_DEV_UNEQUIPPED;

MUTEX_DECL(ina3221_mtx);

/* Moving average calculation objects. */
static ina3221_mon_t mon_ch1;
static ina3221_mon_t mon_ch2;
static ina3221_mon_t mon_ch3;
static ina3221_mon_t mon_ch4;
static ina3221_mon_t mon_ch5;
static ina3221_mon_t mon_ch6;

static const I2CConfig _i2cMainCfg = {
    .op_mode     = OPMODE_I2C,
    .clock_speed = 400000,
    .duty_cycle  = FAST_DUTY_CYCLE_2
};

const pwr_unit_cfg_t pcfg_40 = {
    .drv  = &I2CD1,
    .addr = 0x40,
    .cfg = &_i2cMainCfg
};

const pwr_unit_cfg_t pcfg_41 = {
    .drv  = &I2CD1,
    .addr = 0x41,
    .cfg = &_i2cMainCfg
};

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

bool sysReadI2C16(I2CDriver *bus, const I2CConfig *cfg, i2caddr_t addr,
                  uint8_t reg, uint16_t *val) {
    uint8_t txbuf[] = {reg};
    uint8_t rxbuf[2];

    i2cStart(bus, cfg);
    msg_t i2c_status = i2cMasterTransmitTimeout(bus, addr, txbuf, 1, rxbuf, 2, TIME_MS2I(100));
    i2cStop(bus);

    *val =  (rxbuf[0] << 8) | rxbuf[1];
    return i2c_status == MSG_OK;
}

bool sysWriteI2CN(I2CDriver *bus, const I2CConfig *cfg, i2caddr_t addr,
                  uint8_t *txbuf, uint32_t length) {

    i2cStart(bus, cfg);
    msg_t i2c_status = i2cMasterTransmitTimeout(bus, addr, txbuf, length, NULL, 0, TIME_MS2I(100));
    i2cStop(bus);

    return i2c_status == MSG_OK;
}

/**
 *
 */
static void ina3221_lock(void) {
  chMtxLock(&ina3221_mtx);
}

/**
 *
 */
static void ina3221_unlock(void) {
  chMtxUnlock(&ina3221_mtx);
}

/**
 *
 */
static bool ina3221_get_chan(const pwr_unit_cfg_t* pcfg, ina3221_chan_t *chan, ina3221_rad_t addr) {
  bool ret = false;
  if (!sysReadI2C16(pcfg->drv, pcfg->cfg, pcfg->addr, addr,
                                      (ina3221_rreg_t *)&chan->shunt)) {
    chan->shunt = (ina3221_vreg_t)0;
    ret |= true;
  }
  if (!sysReadI2C16(pcfg->drv, pcfg->cfg, pcfg->addr, addr + 1,
                                      (ina3221_rreg_t *)&chan->bus)) {
    chan->bus = (ina3221_vreg_t)0;
    ret |= true;
  }
  return !ret;
}

/**
 *
 */
static void ina3221_update_chan(const pwr_unit_cfg_t* pcfg, ina3221_mon_t *mon, ina3221_rad_t addr) {

  ina3221_chan_t chan;
  ina3221_lock();
  if (ina3221_get_chan(pcfg, &chan, addr)) {
    mon->bus_volt   = chan.bus;
    mon->shunt_volt = chan.shunt;
    (void)mon;
  }
  ina3221_unlock();
}

/**
 *
 */
//static void ina3221_init_chan(pwr_unit_cfg_t* pcfg, ina3221_mon_t *mon, ina3221_rad_t addr) {
//
//  ina3221_chan_t chan;
//  (void)ina3221_get_chan(pcfg, &chan, addr);
//  //monMovingAverageFilterInit(&mon->bus, chan.bus);
//  //monMovingAverageFilterInit(&mon->shunt, chan.shunt);
//  (void)mon;
//}

/**
 *
 */
static void ina3221_hardware_reset(const pwr_unit_cfg_t *pcfg) {
  uint8_t conf[] = {INA3221_CONFIGURATION, 0x80, 0x00};
  if (!sysWriteI2CN(pcfg->drv, pcfg->cfg, pcfg->addr, conf,
                                                      sizeof(conf))) {
    //CTRACE(TL_ERR, TS_PMGR,"Could not reset chip");
    error |= 0x2;
  }
}

/**
 * Configuration
 */
static void ina3221_send_config(const pwr_unit_cfg_t *pcfg) {
  /* MODE = 7 (continuous sh & bus), Vsh = 100 (1.1mS), Vbus = 100 (1.1mS),
     AVG = 16, CH = 1,2 & 3.*/
  uint8_t conf[] = {INA3221_CONFIGURATION, 0x75, 0x27};
  uint16_t conf_read;
  if (!sysWriteI2CN(pcfg->drv, pcfg->cfg, pcfg->addr, conf,
                                                            sizeof(conf))) {
    //CTRACE(TL_ERR, TS_PMGR,"Could not send configuration");
    error |= 0x2;
  }

  chThdSleep(TIME_MS2I(50));
  if (!sysReadI2C16(pcfg->drv, pcfg->cfg, pcfg->addr,
                                      INA3221_CONFIGURATION, &conf_read)) {
    //CTRACE(TL_ERR, TS_PMGR,"Could not read configuration");
    error |= 0x2;
    return;
  }

  if (conf_read != 0x7527) {
    //CTRACE(TL_ERR, TS_PMGR,"Wrong configuration in register");
    error |= 0x2;
  }
}

/*===========================================================================*/
/* Module external functions.                                                */
/*===========================================================================*/

/**
 *
 */
bool ina3221_isAvailable(const pwr_unit_cfg_t* pcfg) {

  uint16_t man, die;

  if (!sysReadI2C16(pcfg->drv, pcfg->cfg, pcfg->addr,
                                            INA3221_MANUFACTURER_ID, &man) ||
      !sysReadI2C16(pcfg->drv, pcfg->cfg, pcfg->addr,
                                                  INA3221_DIE_ID, &die)) {
    //CTRACE(TL_ERR, TS_PMGR, "Could not find INA3221");
    error |= MON_DEV_UNEQUIPPED;
    return false; // Device unresponsive
  }

  if (man != 0x5449 || die != 0x3220) {
    //CTRACE(TL_ERR, TS_PMGR, "INA3221 returned wrong Manufacturer/Die ID");
    error |= MON_DEV_FAULT;
    return false; // Wrong chip
  }
  return true;
}

/**
 * @brief Calculate and return the voltage or power reading
 */
msg_t ina3221_get_current_reading(const mon_source_t *source, mon_reading_t *mrp) {

  float calc;
  *mrp = 0xFFFFFFFF;
  ina3221_lock();
  switch (source->compute) {
    case MON_NMWATT: {
      switch (source->ports) {
        case  MON_PORT_1:
          calc = (float)mon_ch1.shunt_volt * 5.0 / INA3221_CH1_RSENSE; // uA
          *mrp = (mon_reading_t)(calc * (float)mon_ch1.bus_volt / 1000000.0);
          break;

        case  MON_PORT_2:
          calc = (float)mon_ch2.shunt_volt * 5.0 / INA3221_CH2_RSENSE; // uA
          *mrp = (mon_reading_t)(calc * (float)mon_ch2.bus_volt / 1000000.0);
          break;

        case  MON_PORT_3:
          calc = (float)mon_ch3.shunt_volt * 5.0 / INA3221_CH3_RSENSE; // uA
          *mrp = (mon_reading_t)(calc * (float)mon_ch3.bus_volt / 1000000.0);
          break;

        case  MON_PORT_4:
          calc = (float)mon_ch4.shunt_volt * 5.0 / INA3221_CH4_RSENSE; // uA
          *mrp = (mon_reading_t)(calc * (float)mon_ch4.bus_volt / 1000000.0);
          break;

        case  MON_PORT_5:
          calc = (float)mon_ch5.shunt_volt * 5.0 / INA3221_CH5_RSENSE; // uA
          *mrp = (mon_reading_t)(calc * (float)mon_ch5.bus_volt / 1000000.0);
          break;

        case  MON_PORT_6:
          calc = (float)mon_ch6.shunt_volt * 5.0 / INA3221_CH6_RSENSE; // uA
          *mrp = (mon_reading_t)(calc * (float)mon_ch6.bus_volt / 1000000.0);
          break;

        default:
          return MSG_ERROR;
      }
      break;
    }

    case MON_NMVOLT: {
      switch (source->ports) {
        case  MON_PORT_1:
          *mrp = (mon_reading_t)(mon_ch1.bus_volt);
          break;

        case  MON_PORT_2:
          *mrp = (mon_reading_t)(mon_ch2.bus_volt);
          break;

        case  MON_PORT_3:
          *mrp = (mon_reading_t)(mon_ch3.bus_volt);
          break;

        case  MON_PORT_4:
          *mrp = (mon_reading_t)(mon_ch4.bus_volt);
          break;

        case  MON_PORT_5:
          *mrp = (mon_reading_t)(mon_ch5.bus_volt);
          break;

        case  MON_PORT_6:
          *mrp = (mon_reading_t)(mon_ch6.bus_volt);
          break;

        default:
          return MSG_ERROR;
      }
      break;
    }

    /* Unknown type.*/
    default:
      return MSG_ERROR;

  }
  ina3221_unlock();
  return MSG_OK;
}

/**
 * Power monitoring thread.
 */
THD_FUNCTION(ina3221_thd, arg)
{
  (void)arg;

  // Setup pins
  palSetLineMode(PAL_LINE(GPIOB, 6), PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN);
  palSetLineMode(PAL_LINE(GPIOB, 7), PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN);

  /* Reset and then send config to chip. */
  ina3221_hardware_reset(&pcfg_40);
  chThdSleep(TIME_MS2I(100));
  ina3221_send_config(&pcfg_40);
  chThdSleep(TIME_MS2I(100));

  /* Reset and then send config to chip. */
  ina3221_hardware_reset(&pcfg_41);
  chThdSleep(TIME_MS2I(100));
  ina3221_send_config(&pcfg_41);
  chThdSleep(TIME_MS2I(100));

  /* Start update loop.*/
  while (true) {
    /* Update power manager readings.*/
    ina3221_update_chan(&pcfg_40, &mon_ch1, INA3221_CHAN1_REGS);
    ina3221_update_chan(&pcfg_40, &mon_ch2, INA3221_CHAN2_REGS);
    ina3221_update_chan(&pcfg_40, &mon_ch3, INA3221_CHAN3_REGS);
    ina3221_update_chan(&pcfg_41, &mon_ch4, INA3221_CHAN1_REGS);
    ina3221_update_chan(&pcfg_41, &mon_ch5, INA3221_CHAN2_REGS);
    ina3221_update_chan(&pcfg_41, &mon_ch6, INA3221_CHAN3_REGS);
    chThdSleep(TIME_MS2I(500));
  }
}

/**
 *
 */
bool ina3221_start(void)
{
    //if(chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(512), "INA3221",
    //                       NORMALPRIO - 20, ina3221_thd, NULL) == NULL) {
    //    return false;
    //}
    chThdSleep(TIME_MS2I(10));

    return true;
}
