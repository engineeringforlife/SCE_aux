#include "Arduino.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_task_wdt.h"

/* The two task functions. */
void vTask1( void *pvParameters );
void vTask2( void *pvParameters );

/* Used to hold the handle of Task2. */
TaskHandle_t xTask2Handle;

/*-----------------------------------------------------------*/

void setup( void )
{
  Serial.begin(115200);
  /* Create the first task at priority 1.  This time the task parameter is
    not used and is set to NULL.  The task handle is also not used so likewise
    is also set to NULL. */
  xTaskCreatePinnedToCore( vTask1, "Task 1", 1024, NULL, 1, NULL, 1);
  /* The task is created at priority 1 ^. */

  /* Start the scheduler so our tasks start executing. */
  //vTaskStartScheduler();

  //  for( ;; );
  //  return 0;
}
/*-----------------------------------------------------------*/

void vTask1( void *pvParameters )
{
  const TickType_t xDelay100ms = 100 / portTICK_PERIOD_MS;

  for ( ;; )
  {
    /* Print out the name of this task. */
    Serial.print( "EX9: Task1 is running\r\n" );

    /* Create task 2 at a higher priority.  Again the task parameter is not
      used so is set to NULL - BUT this time we want to obtain a handle to the
      task so pass in the address of the xTask2Handle variable. */
    xTaskCreatePinnedToCore( vTask2, "Task 2", 1024, NULL, 2, &xTask2Handle, 1);
    /* The task handle is the last parameter ^^^^^^^^^^^^^ */

    /* Task2 has/had the higher priority, so for Task1 to reach here Task2
      must have already executed and deleted itself.  Delay for 100
      milliseconds. */
    vTaskDelay( xDelay100ms );
  }
}

/*-----------------------------------------------------------*/

void vTask2( void *pvParameters )
{
  /* Task2 does nothing but delete itself.  To do this it could call vTaskDelete()
    using a NULL parameter, but instead and purely for demonstration purposes it
    instead calls vTaskDelete() with its own task handle. */
  Serial.print( "EX9: Task2 is running and about to delete itself\r\n" );
  vTaskDelete( xTask2Handle );
}
/*-----------------------------------------------------------*/
void loop()
{
  vTaskDelete( NULL );
}
