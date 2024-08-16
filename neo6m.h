

#ifndef SG90_H_
#define SG90_H_

#include <stdio.h>
#include <sys/_intsup.h>
#include "driver/ledc.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "hal/ledc_types.h"
#include "portmacro.h"
#include "esp_log.h"

//PWM settings
#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO          (5) // Define the output GPIO
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_DUTY               (819) // Set duty to 50%. (2 ** 13) * 50% = 4096
#define LEDC_FREQUENCY          (50) // Frequency in Hertz. Set frequency at 4 kHz

void servo_init(void);
void servo_swerve(void);
void servo_pos(int pos);
void parse_nmea(const char *buf, char *latitude, char *longitude);


#endif 
