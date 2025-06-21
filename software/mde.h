#ifndef _MDE_H_
#define _MDE_H_

#include "ch.h"
#include "hal.h"

#define LINE_MDE_MOSI   PAL_LINE(GPIOC, 12)
#define LINE_MDE_MISO   PAL_LINE(GPIOC, 11)
#define LINE_MDE_SCK    PAL_LINE(GPIOC, 10)
#define LINE_MDE_CS     PAL_LINE(GPIOD, 13)
#define LINE_MDE_PWR    PAL_LINE(GPIOD, 0)

#define MOTOR_AZ    0b011
#define MOTOR_EL    0b101
#define MOTOR_SK    0b110

void mde_init(void);

void mde_power_up(void);
void mde_power_down(void);

uint16_t mde_get_az_enc_pos(void);
int16_t mde_get_az_enc_spd(void);

int8_t mde_get_trq_az(void);
void mde_set_trq_az(int8_t trq);
int8_t mde_get_trq_el(void);
void mde_set_trq_el(int8_t trq);
int8_t mde_get_trq_sk(void);
void mde_set_trq_sk(int8_t trq);

uint16_t mde_get_az_enc_off(void);
void mde_set_az_enc_off(uint16_t off);

#endif
