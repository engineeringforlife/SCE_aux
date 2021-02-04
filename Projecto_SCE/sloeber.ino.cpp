#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2021-02-04 19:00:43

#include "Arduino.h"
#include "Arduino.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include <Wire.h>
#include <rhio-LIS2HH12.h>

void setup( void ) ;
void loop() ;
static void vSenderSI7006_HUM( void *pvParameters ) ;
static void vSenderSI7006_TEMP( void *pvParameters ) ;
static void vSenderLTR329ALS01( void *pvParameters ) ;
static void vSenderLIS2HH12( void *pvParameters ) ;
static void vReceiverTask( void *pvParameters ) ;

#include "Projecto_SCE.ino"


#endif
