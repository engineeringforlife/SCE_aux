#include "Arduino.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_task_wdt.h"

#define mainDELAY_LOOP_COUNT    400000 //( 0xffffff )

/* The task functions. */
void vContinuousProcessingTask( void *pvParameters );
void vPeriodicTask( void *pvParameters );

/* Define the strings that will be passed in as the task parameters.  These are
  defined const and off the stack to ensure they remain valid when the tasks are
  executing. */
const char *pcTextForTask1 = "EX6: Continuous task 1 running\r\n";
const char *pcTextForTask2 = "EX6: Continuous task 2 running\r\n";
const char *pcTextForPeriodicTask = "EX6: Periodic task 3 is running *************\r\n";

/*-----------------------------------------------------------*/

void setup( void )
{
  Serial.begin(115200);
  /* Create two instances of the continuous processing task, both at priority 1. */
  xTaskCreatePinnedToCore( vContinuousProcessingTask, "Task 1", 1024, (void*)pcTextForTask1, 1, NULL, 0);
  xTaskCreatePinnedToCore( vContinuousProcessingTask, "Task 2", 1024, (void*)pcTextForTask2, 1, NULL, 1);

  /* Create one instance of the periodic task at priority 2. */
  xTaskCreatePinnedToCore( vPeriodicTask, "Task 3", 1024, (void*)pcTextForPeriodicTask, 2, NULL, 1);

  /* Start the scheduler so our tasks start executing. */
  //vTaskStartScheduler();

  //  for( ;; );
  //  return 0;
}
/*-----------------------------------------------------------*/

void vContinuousProcessingTask( void *pvParameters )
{
  char *pcTaskName;
  volatile unsigned long ul;

  /* The string to print out is passed in via the parameter.  Cast this to a
    character pointer. */
  pcTaskName = ( char * ) pvParameters;

  /* As per most tasks, this task is implemented in an infinite loop. */
  for ( ;; )
  {
    /* Print out the name of this task.  This task just does this repeatedly
      without ever blocking or delaying. */
    Serial.print( pcTaskName );
    for ( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
    {
      /* This loop is just a very crude delay implementation.  There is
        nothing to do in here.  Later exercises will replace this crude
        loop with a proper delay/sleep function. */
    }
  }
}
/*-----------------------------------------------------------*/

void vPeriodicTask( void *pvParameters )
{
  TickType_t xLastWakeTime;
  char *pcTaskName;

  /* The string to print out is passed in via the parameter.  Cast this to a
    character pointer. */
  pcTaskName = ( char * ) pvParameters;

  /* The xLastWakeTime variable needs to be initialized with the current tick
    count.  Note that this is the only time we access this variable.  From this
    point on xLastWakeTime is managed automatically by the vTaskDelayUntil()
    API function. */
  xLastWakeTime = xTaskGetTickCount();

  /* As per most tasks, this task is implemented in an infinite loop. */
  for ( ;; )
  {
    /* Print out the name of this task. */
    //Serial.println( "Periodic task is running\r\n" );
    Serial.println( pcTaskName );
    /* We want this task to execute exactly every 500 milliseconds. */
    vTaskDelayUntil( &xLastWakeTime, ( 500 / portTICK_PERIOD_MS ) );
  }
}
//------------------------------------------------------------------------------
void loop()
{
  vTaskDelete( NULL );
}
