#include "Arduino.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_task_wdt.h"
#include "esp_freertos_hooks.h"

/* The task function. */
void vTaskFunction( void *pvParameters );

/* A variable that is incremented by the idle task hook function. */
volatile unsigned long ulIdleCycleCount = 0UL;

/* Define the strings that will be passed in as the task parameters.  These are
  defined const and off the stack to ensure they remain valid when the tasks are
  executing. */
const char *pcTextForTask1 = "EX7: Task 1 is running\r\n";
const char *pcTextForTask2 = "EX7: Task 2 is running\t\n";

/*-----------------------------------------------------------*/

void setup( void )
{
  Serial.begin(115200);
  esp_register_freertos_idle_hook(my_vApplicationIdleHook);
  /* Create the first task at priority 1... */
  xTaskCreatePinnedToCore( vTaskFunction, "Task 1", 1024, (void*)pcTextForTask1, 1, NULL, 1);

  /* ... and the second task at priority 2.  The priority is the second to
    last parameter. */
  xTaskCreatePinnedToCore( vTaskFunction, "Task 2", 1024, (void*)pcTextForTask2, 2, NULL, 1);

  /* Start the scheduler so our tasks start executing. */
  //vTaskStartScheduler();

  //  for( ;; );
  //  return 0;
}
/*-----------------------------------------------------------*/

void vTaskFunction( void *pvParameters )
{
  char *pcTaskName;

  /* The string to print out is passed in via the parameter.  Cast this to a
    character pointer. */
  pcTaskName = ( char * ) pvParameters;

  /* As per most tasks, this task is implemented in an infinite loop. */
  for ( ;; )
  {
    /* Print out the name of this task AND the number of times ulIdleCycleCount
        has been incremented. */
    Serial.print( pcTaskName);
    Serial.println(ulIdleCycleCount);

    /* Delay for a period.  This time we use a call to vTaskDelay() which
      puts the task into the Blocked state until the delay period has expired.
      The delay period is specified in 'ticks'. */
    vTaskDelay( 250 / portTICK_PERIOD_MS );
  }
}
/*-----------------------------------------------------------*/

/* Idle hook functions MUST be called vApplicationIdleHook(), take no parameters,
  and return void. */
//extern "C"{ // FreeRTOS expects C linkage
bool my_vApplicationIdleHook( void )
{
  /* This hook function does nothing but increment a counter. */
  ulIdleCycleCount++;
  return true;
}
//}
//------------------------------------------------------------------------------
void loop()
{
  vTaskDelete( NULL );
}
