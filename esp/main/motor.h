#pragma once

#include <esp_system.h>
#include <esp_log.h>
#include "driver/ledc.h"
#include "esp_err.h"
#include <stdio.h>
#include <string.h>

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO          (5) // Define the output GPIO
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_DUTY               (4095) // Set duty to 50%. ((2 ** 13) - 1) * 50% = 4095
#define LEDC_FREQUENCY          (200) // Frequency in Hertz. Set frequency at 5 kHz

void handle_motors(char*, int);