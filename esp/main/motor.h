#pragma once

#include <esp_system.h>
#include <esp_log.h>
#include "driver/ledc.h"
#include "esp_err.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_LEFT        (17) // Define the output GPIO
#define LEDC_OUTPUT_RIGHT       (5) // Define the output GPIO
#define LEDC_CHANNEL_L          LEDC_CHANNEL_0
#define LEDC_CHANNEL_R          LEDC_CHANNEL_1
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_FREQUENCY          (200) // Frequency in Hertz. Set frequency at 5 kHz

#define X_MAX 90
#define Y_MAX 90

void parse_motor_msg(char*, int);

void move_motor(float, float);

void motor_init(void);