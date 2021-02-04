#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2021-01-17 19:34:19

#include "Arduino.h"
#include "Arduino.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_task_wdt.h"

void setup( void ) ;
static void vHandlerTask( void *pvParameters ) ;
static void vPeriodicTask( void *pvParameters ) ;
static void IRAM_ATTR vExampleInterruptHandler( void ) ;
void loop() ;

#include "Ex13_semaphor.ino"


#endif
