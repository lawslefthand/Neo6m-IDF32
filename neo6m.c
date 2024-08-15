#include "neo6m.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/_intsup.h>
#include <unistd.h>
#include "driver/uart.h"
#include "esp_err.h"
#include "freertos/idf_additions.h"
#include "hal/uart_types.h"
#include "portmacro.h"
#include "esp_log.h"

static const char *TAG = "GPS_MODULE";

void gps_start(void)
{   
    const uart_port_t uart_num = UART_NUM_0;
    uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };
    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(uart_num, 1, 3, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
    ESP_ERROR_CHECK(uart_driver_install(uart_num, BUFFER, 0, 0, NULL, 0));
}

void raw_nmea(void)
{
    char buf[BUFFER];
    uart_read_bytes(UART_NUM_0, buf, BUFFER, portMAX_DELAY);
    ESP_LOGI(TAG, "%s", buf);
}

void lat_long(void)
{
    char buf[BUFFER];
    char lat[12];
    char lon[12];
    uart_read_bytes(UART_NUM_0, buf, BUFFER, 20 / portTICK_PERIOD_MS);
    sscanf(buf, "$GPGGA,%*f,%11[^,],%*c,%11[^,],%*c", lat, lon);
    ESP_LOGI(TAG, "Latitude is:%s", lat);
    ESP_LOGI(TAG, "Longitude is:%s", lon);
}

void time(void)
{
    char buf[BUFFER];
    char time[20];
    uart_read_bytes(UART_NUM_0, buf, BUFFER, 20 / portTICK_PERIOD_MS);
    sscanf(buf, "$GPGGA,%6[^,],", time); 
    ESP_LOGI(TAG, "Time is %s", time); 
}

void speed_course(void)
{
    char buf[BUFFER];
    float speedKmh;
    float course;
    uart_read_bytes(UART_NUM_0, buf, BUFFER, 20 / portTICK_PERIOD_MS);
    sscanf(buf, "$GPVTG,%*f,%*c,%*f,%*c,%*f,%*c,%f", &speedKmh); 
    sscanf(buf, "$GPVTG,%f", &course); 
    sscanf(buf, "$GPRMC,%*f,%*c,%*f,%*c,%*f,%*c,%*f,%f", &course); 
    ESP_LOGI(TAG, "Speed is %f", speedKmh); 
    ESP_LOGI(TAG, "Course is %f", course); 
}