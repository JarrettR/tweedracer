#include "motor.h"

static const char *TAG = "MOTOR";

static int ledc_duty(float percent) {
    //#define LEDC_DUTY               (4095) // Set duty to 50%. ((2 ** 13) - 1) * 50% = 4095

    const float total = 8191;

    return (int) (total * percent) ;
}

void motor_init(void)
{
    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .timer_num        = LEDC_TIMER,
        .duty_resolution  = LEDC_DUTY_RES,
        .freq_hz          = LEDC_FREQUENCY,  // Set output frequency at 5 kHz
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel_l = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL_L,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_LEFT,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel_l));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel_r = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL_R,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_RIGHT,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel_r));
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

    float motor_max = fabs(y / Y_MAX);
    float weight = fabs(x / X_MAX);
    float lPercent, rPercent;

    int direction;

    if (y > 0) {
        direction = 0:
    } else {
        direction = 1;
    }

    
    if (x > 0) {
        rPercent = motor_max;
        lPercent = (1 - weight) * motor_max;
    } else {
        lPercent = motor_max;
        rPercent = (1 - weight) * motor_max;
    }
    ESP_LOGI(TAG, "M: %f    W: %f", motor_max, weight);
    ESP_LOGI(TAG, "L: %f    R: %f", lPercent, rPercent);

    int lDuty = ledc_duty(lPercent);
    int rDuty = ledc_duty(rPercent);

    ESP_LOGI(TAG, "L: %d    R: %d", lDuty, rDuty);
    
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_L, lDuty));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_L));
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_R, rDuty));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_R));

}