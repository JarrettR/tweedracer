#include "motor.h"

static const char *TAG = "MOTOR";


static void motor_init(void)
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
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_IO,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}

void handle_motors(char* message, int size) {
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

}