#pragma once

#define MOTOR_L_A               18
#define MOTOR_L_B               17
#define MOTOR_R_A               16
#define MOTOR_R_B               4

void parse_motor_msg(char*, int);

void move_motor(float, float);

void motor_init(void);