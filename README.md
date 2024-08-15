# Neo6m-IDF32
Driver for Neo6m for the Esp32 series of Mcus for use in Esp-IDF.

The driver enables the ESP32 to communicate with the Neo-6M GPS module via UART and parse essential GPS data such as latitude, longitude, time, speed, and course.

Features

*UART Initialization (gps_start)
Configures the UART interface for communication with the Neo-6M GPS module.
Sets the baud rate to 9600, with 8 data bits, 1 stop bit, and no parity.
Disables hardware flow control to simplify communication.
Installs the UART driver and assigns appropriate pins.

*Raw NMEA Sentence Retrieval (raw_nmea)
Reads the raw NMEA sentences directly from the GPS module.
Logs the complete NMEA sentence to the ESP32 console for debugging or further processing.

*Latitude and Longitude Extraction (lat_long)
Extracts the latitude and longitude information from the NMEA sentences.
Logs the latitude and longitude values, allowing for easy integration into location-based applications.

*Time Extraction (time)
Extracts the time information from the NMEA sentences, specifically from the $GPGGA sentence.
Logs the time in a human-readable format.

*Speed and Course Extraction (speed_course)
Extracts the speed (in kilometers per hour) and course information from the NMEA sentences.
Supports parsing of both $GPVTG and $GPRMC sentences for comprehensive data.
Logs the speed and course values, making it useful for tracking movement and direction.
Usage
To use this driver, include the neo6m.h header in your project, and call the relevant functions as needed. The driver is designed to be easily integrated into applications requiring GPS data, such as navigation systems, location trackers, or any project involving geolocation.


Example code - 

```
#include <stdint.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "neo6m.h"



void task(void *arg)
{
	gps_start(); //avoid using gps_start() again until and unless driver is not de-inited properly.
	 while(1)
	 {
	  raw_nmea();
	  lat_long();
	  time();
	  speed_course();
     }
}

// use uart_driver_delete(UART_NUM_0) when done with UART to avoid collision with other periphrals.


void app_main(void)
{
    
    xTaskCreatePinnedToCore(&task, "test", 4092*2, NULL, 5, NULL, 1);
    
    
}
```

Refrence serial image:

![image](https://github.com/user-attachments/assets/45dc4bf1-aa59-44a4-934c-96968031cf9f)

