/*
 * neo6m.h
 *
 *  Created on: 15-Aug-2024
 *      Author: danba
 */

#ifndef MAIN_NEO6M_H_
#define MAIN_NEO6M_H_

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

#define BUFFER 1024*2

 void gps_start(void);
 void raw_nmea(void);
 void lat_long(void);
 void speed_course(void);
 void time(void);




#endif /* MAIN_NEO6M_H_ */
