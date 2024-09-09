# Neo6m-IDF32
Driver for Neo-6M GPS module for the ESP32 series of MCUs, designed for use with Espressif's IoT Development Framework (ESP-IDF).

The driver enables the ESP32 to communicate with the Neo-6M GPS module via UART and display essential GPS data such as latitude, longitude, time, speed, and course. It is built to integrate seamlessly into projects requiring GPS data.

## Features

- **UART Initialization (`gps_start`)**  
  Configures the UART interface for communication with the Neo-6M GPS module.  
  - Baud rate: 9600
  - Data bits: 8
  - Stop bit: 1
  - No parity
  - Hardware flow control is disabled to simplify communication.  
  Installs the UART driver and assigns the appropriate pins.

- **Raw NMEA Sentence Retrieval (`raw_nmea`)**  
  Reads the raw NMEA sentences directly from the GPS module.  
  Logs the complete NMEA sentence to the ESP32 console for debugging or further processing.

## NMEA Sentences Usage

The driver supports the retrieval of GPS data from various NMEA sentences:

- **Latitude and Longitude**  
  The `$GPGGA` sentence provides latitude and longitude values, making it easy to integrate into location-based applications.

- **Time**  
  Time data can also be retrieved from the `$GPGGA` sentence.

- **Speed and Course**  
  Speed (in kilometers per hour) and course information can be extracted from the `$GPVTG` and `$GPRMC` sentences, making the driver useful for tracking movement and direction.

## Usage

To use this driver:

1. Include the `neo6m.h` header in your project.
2. Call the relevant functions as needed.

The driver is designed to be easily integrated into applications requiring GPS data, such as navigation systems, location trackers, or any project involving geolocation.


Example code - 

```
#include <stdint.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "neo6m.h"

//IMPORTANT : Always invoke gps_start() and then raw_nmea()

void task(void *arg)
{
	gps_start(); //avoid using gps_start() again until and unless driver is not de-inited properly.
	 while(1)
	 {
	  raw_nmea(); // always use before any of the lat_long , time , speed_course functions
	 
     }
}

// use uart_driver_delete(UART_NUM_0) when done with UART to avoid collision with other periphrals.


void app_main(void)
{
    
    xTaskCreatePinnedToCore(&task, "test", 4092*2, NULL, 5, NULL, 1);
    
    
}
```

Experimental functions: lat_long(),time() and speed_course() use manual parsing and may give unexpected results. Use at your own risk.

