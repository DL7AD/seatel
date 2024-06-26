#include "ctrl.h"
#include "mde.h"
#include "api.h"
#include "imu.h"
#include "debug.h"
#include "chprintf.h"
#include <stdlib.h>
#include <math.h>

static bool az_flag_calibrate = false;

static motor_state_t az_state = MOTOR_STATE_CONST_TORQUE;
static motor_state_t el_state = MOTOR_STATE_CONST_TORQUE;
static motor_state_t sk_state = MOTOR_STATE_CONST_TORQUE;

static int16_t az_tgt_spd = 0;       // Azimuth Target Speed
static uint16_t az_tgt_pos = 0;      // Azimuth Target Position
static int16_t az_tgt_pos_spd = 0;   // Azimuth Target Position Speed
static systime_t az_tgt_pos_tim = 0; // Azimuth Target Position Update Time

static int16_t el_tgt_spd = 0;       // Elevation Target Speed
static int16_t el_tgt_pos = 0;       // Elevation Target Position
static int16_t el_tgt_pos_spd = 0;   // Elevation Target Position Speed
static systime_t el_tgt_pos_tim = 0; // Elevation Target Position Update Time

static int16_t sk_tgt_pos = 0;


void az_set_const_trq(int8_t torque) {
    az_flag_calibrate = false;
    az_state = MOTOR_STATE_CONST_TORQUE;
    mde_set_trq_az(torque);
}

void el_set_const_trq(int8_t torque) {
    mde_set_trq_el(torque);
    el_state = MOTOR_STATE_CONST_TORQUE;
}

void sk_set_const_trq(int8_t torque) {
    mde_set_trq_sk(torque);
    sk_state = MOTOR_STATE_CONST_TORQUE;
}

void az_set_const_spd(int16_t speed) {
    az_tgt_spd = speed;
    az_flag_calibrate = false;
    az_state = MOTOR_STATE_CONST_SPEED;
}

void az_set_tgt_pos(uint16_t position) {
    az_tgt_pos = position;
    az_flag_calibrate = false;
    az_tgt_pos_tim = chVTGetSystemTimeX();
    az_state = MOTOR_STATE_TARGET_POSITION;
}

void az_set_tgt_pos_spd(int16_t speed) {
    az_tgt_pos_spd = speed;

    char buf[64];
    uint32_t ms = TIME_I2MS(chVTGetSystemTimeX());
    chsnprintf(buf, sizeof(buf), "[%.3f] az_spd=%d\n",
        ms/1000.0, speed);
    debug_print(buf);
}

void el_set_tgt_pos(int16_t position) {
    el_tgt_pos = position;
    el_tgt_pos_tim = chVTGetSystemTimeX();
    el_state = MOTOR_STATE_TARGET_POSITION;
}

void el_set_tgt_pos_spd(int16_t speed) {
    el_tgt_pos_spd = speed;

    char buf[64];
    uint32_t ms = TIME_I2MS(chVTGetSystemTimeX());
    chsnprintf(buf, sizeof(buf), "[%.3f] el_spd=%d\n",
        ms/1000.0, speed);
    debug_print(buf);
}

void sk_set_tgt_pos(int16_t position) {
    sk_tgt_pos = position;
    sk_state = MOTOR_STATE_TARGET_POSITION;
}

uint16_t az_get_tgt_pos(void) {
    return az_tgt_pos;
}

int16_t el_get_tgt_pos(void) {
    return el_tgt_pos;
}

int16_t sk_get_tgt_pos(void) {
    return sk_tgt_pos;
}

motor_state_t az_get_state(void) {
    return az_state;
}

motor_state_t el_get_state(void) {
    return el_state;
}

motor_state_t sk_get_state(void) {
    return sk_state;
}

void az_calibrate(void) {
    az_flag_calibrate = true;
}

static THD_WORKING_AREA(waCtrl, 4096);
static THD_FUNCTION(ctrl, arg)
{
    (void)arg;

    uint16_t old_az;
    int8_t dir_el = 0;
    uint32_t cntr = 0;

    while(true)
    {
        // Azimuth calibration
        if(az_flag_calibrate)
        {
            if(az_state != MOTOR_STATE_CONST_SPEED)
            {
                mde_set_trq_az(25);
                chThdSleepMilliseconds(1000);
                az_tgt_spd = 180*30;
                az_state = MOTOR_STATE_CONST_SPEED;
                old_az = 0;
            }
            else
            {
                uint16_t az = mde_get_az_enc_pos();
                if(old_az > az) { // Overflow reached
                    az_set_const_trq(0); // Resets calibration flag
                }
                old_az = az;
            }
        }

        // Azimuth control
        switch(az_state) {
            case MOTOR_STATE_CONST_TORQUE:
                break;

            case MOTOR_STATE_TARGET_POSITION:
            {
                uint16_t enc = mde_get_az_enc_pos();
                uint16_t tgt = az_tgt_pos + az_tgt_pos_spd * TIME_I2MS(chVTGetSystemTimeX()-az_tgt_pos_tim)/1000.0;
                uint16_t dir_diff = tgt-enc;
                uint16_t dist = (uint16_t)(tgt-enc) < (uint16_t)(enc-tgt) ? tgt-enc : enc-tgt;
                uint16_t nullzone = 45;

                if(dir_diff > nullzone && UINT16_MAX-nullzone > dir_diff) {
                    int8_t dir = dir_diff < 32768 ? 1 : -1;
                    az_tgt_spd = dir * dist/2;
                    if(abs(az_tgt_spd) <  2*182) az_tgt_spd = dir* 2*182;
                    if(abs(az_tgt_spd) > 30*182) az_tgt_spd = dir*30*182;
                } else {
                    mde_set_trq_az(mde_get_trq_az() > 0 ? 3 : -3);
                    break;
                }

                [[fallthrough]];
            }
            case MOTOR_STATE_CONST_SPEED:
            {
                int16_t act = mde_get_az_enc_spd();
                int16_t tgt = az_tgt_spd;

                int8_t dir = tgt > 0 ? 1 : -1;
                int8_t static_trq = 10;
                int8_t trq = ((tgt-act)/60) + static_trq * dir;

                if(trq >  25) trq =  25;
                if(trq < -25) trq = -25;

                mde_set_trq_az(trq);
                break;
            }
        }

        // Elevation control
        int16_t imu = imu_get_el_pos();
        int8_t trq0  = -24; // Holding torque required for elevation 0°
        int8_t trq90 =  15; // Holding torque required for elevation 90°
        int8_t static_trq = trq0+(trq90-trq0) * imu / 16384;

        switch(el_state) {
            case MOTOR_STATE_CONST_TORQUE:
                break;

            case MOTOR_STATE_TARGET_POSITION:
            {
                int16_t tgt = el_tgt_pos + el_tgt_pos_spd * TIME_I2MS(chVTGetSystemTimeX()-el_tgt_pos_tim)/1000.0;
                int16_t dist = tgt-imu;
                uint16_t nullzone = 45; // original 91

                el_tgt_spd = dist;
                dir_el = el_tgt_spd < 0 ? -1 : 1;
                if(abs(dist) > nullzone)
                    if(abs(el_tgt_spd) <  1*182) el_tgt_spd = dir_el* 1*182;
                if(abs(el_tgt_spd) > 15*182) el_tgt_spd = dir_el*15*182;

                [[fallthrough]];
            }
            case MOTOR_STATE_CONST_SPEED:
            {
                int16_t spd = imu_get_el_spd();
                int16_t moving_trq = (el_tgt_spd-spd)/10;
                int16_t trq = moving_trq + static_trq;
                if(trq >  30) trq =  30;
                if(trq < -45) trq = -45;
                mde_set_trq_el(trq);
                break;
            }
        }

        // Skew control
        switch(sk_state) {
            case MOTOR_STATE_CONST_TORQUE:
                break;

            case MOTOR_STATE_TARGET_POSITION: // This mode is not supported
                sk_state = MOTOR_STATE_CONST_TORQUE;
                break;

            case MOTOR_STATE_CONST_SPEED: // This mode is not supported
                sk_state = MOTOR_STATE_CONST_TORQUE;
                break;
        }

        if(cntr++%50 == 0)
        {
            char buf[128];
            uint32_t ms = TIME_I2MS(chVTGetSystemTimeX());
            float az = mde_get_az_enc_pos()/182.044;
            float el = imu_get_el_pos()/182.044;
            float tgt_az = az_tgt_pos/182.044;
            float tgt_el = el_tgt_pos/182.044;
            chsnprintf(buf, sizeof(buf), "[%.3f] tgt=(%.2f,%.2f) pos=(%.2f,%.2f) diff=(%.2f,%.2f)\n",
                ms/1000.0, tgt_az, tgt_el, az, el, az-tgt_az, el-tgt_el
            );
            debug_print(buf);
        }

        chThdSleepMilliseconds(10);
    }
}

void ctrl_init(void)
{
    chThdCreateStatic(waCtrl, sizeof(waCtrl), LOWPRIO, ctrl, NULL);
}
