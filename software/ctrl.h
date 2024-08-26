#ifndef _CTRL_H_
#define _CTRL_H_

#include "ch.h"
#include "hal.h"

typedef enum {
    MOTOR_STATE_CONST_TORQUE = 0,
    MOTOR_STATE_CONST_SPEED = 1,
    MOTOR_STATE_TARGET_POSITION = 2
} motor_state_t;

#define MOTOR_STATE(x) ((x)==0 ? "CONST_TORQUE" : (x)==1 ? "CONST_SPEED" : (x)==2 ? "TARGET_POSITION" : "unknown")

void ctrl_init(void);
bool ctrl_is_running(void);

void az_set_const_trq(int8_t torque);
void az_set_const_spd(int16_t speed);
void az_set_tgt_pos(uint16_t position);
void az_set_tgt_pos_spd(int16_t speed);
uint16_t az_get_tgt_pos(void);
motor_state_t az_get_state(void);
void az_calibrate(void);

void el_set_const_trq(int8_t torque);
void el_set_tgt_pos(int16_t position);
void el_set_tgt_pos_spd(int16_t speed);
int16_t el_get_tgt_pos(void);
motor_state_t el_get_state(void);

void sk_set_const_trq(int8_t torque);
void sk_set_tgt_pos(int16_t position);
int16_t sk_get_tgt_pos(void);
motor_state_t sk_get_state(void);

#endif
