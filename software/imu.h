#ifndef _IMU_H_
#define _IMU_H_

#include "ch.h"
#include "hal.h"

#define LINE_IMU_MOSI   PAL_LINE(GPIOB, 15)
#define LINE_IMU_MISO   PAL_LINE(GPIOB, 14)
#define LINE_IMU_SCK    PAL_LINE(GPIOB, 10)

#define LINE_IMU_CS1    PAL_LINE(GPIOE, 5)
#define LINE_IMU_CS2    PAL_LINE(GPIOE, 4)
#define LINE_IMU_CS3    PAL_LINE(GPIOE, 3)
#define LINE_IMU_MPU    PAL_LINE(GPIOE, 6)

#define LINE_IMU_EN     PAL_LINE(GPIOE, 2)
//#define LINE_IMU_MYSTERY PAL_LINE(GPIOA, 5)

void imu_init(void);

int16_t imu_get_accel_x(void);
int16_t imu_get_accel_y(void);
int16_t imu_get_accel_z(void);

uint16_t imu_get_rot_x(void);
uint16_t imu_get_rot_y(void);
uint16_t imu_get_rot_z(void);

int16_t imu_get_el_pos(void);
int16_t imu_get_el_spd(void);

void imu_calibrate(void);

#endif
