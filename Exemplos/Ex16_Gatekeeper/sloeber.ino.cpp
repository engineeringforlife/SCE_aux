#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2021-01-17 19:34:21

#include "Arduino.h"
#include "Arduino.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_task_wdt.h"
#include "esp_freertos_hooks.h"

void setup( void ) ;
static void prvStdioGatekeeperTask( void *pvParameters ) ;
bool my_vApplicationIdleHook( void )   ;
static void prvPrintTask( void *pvParameters ) ;
void loop() ;

#include "Ex16_Gatekeeper.ino"


#endif
