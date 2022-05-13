#include <esp_system.h>
#include <esp_log.h>
#include "driver/gpio.h"
#include "esp_err.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "motor.h"

static const char *TAG = "MOTOR";

void motor_init(void)
{
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, MOTOR_L_A);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, MOTOR_L_B);

    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1A, MOTOR_R_A);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1B, MOTOR_R_B);

    mcpwm_config_t pwm_config;
    pwm_config.frequency = 200;
    pwm_config.cmpr_a = 0;    //duty cycle of PWMxA = 0
    pwm_config.cmpr_b = 0;    //duty cycle of PWMxb = 0
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_1, &pwm_config);
}

void parse_motor_msg(char* message, int size) {
    char xStr[size];
    char yStr[size];
    char *current = xStr;
    int xlength = 0;
    int i;
    float x,y;


    for (i = 0; i < size; i++)
    {
        if (message[i] == ',') {
            current[i] = '\0';
            current = yStr;
            xlength = i + 1;
        } else {
            current[i - xlength] = message[i];
        }

    }
    current[i - xlength] = '\0';

    ESP_LOGI(TAG, "X: %s    Y:%s", xStr, yStr);

    x = atof(xStr);
    y = atof(yStr);
    move_motor(x, y);

}


void move_motor(float x, float y) {
    //    -
    //  -   +
    //    +

    float motor_max = fabs(y);
    float weight = fabs(x);
    float lPercent, rPercent;

    if (x < 0.0f) {
        rPercent = 100.0f * motor_max;
        lPercent = 100.0f * (1.0f - weight) * motor_max;
    } else {
        lPercent = 100.0f * motor_max;
        rPercent = 100.0f * (1.0f - weight) * motor_max;
    }

    ESP_LOGI(TAG, "M: %f    W: %f", motor_max, weight);
    ESP_LOGI(TAG, "L: %f    R: %f", lPercent, rPercent);

    if (y < 0.0f) {
        mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B);
        mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, lPercent);
        mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);

        mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_B);
        mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A, rPercent);
        mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
    } else {
        mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A);
        mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, lPercent);
        mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, MCPWM_DUTY_MODE_0);

        mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A);
        mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_B, rPercent);
        mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_B, MCPWM_DUTY_MODE_0);
    }

}