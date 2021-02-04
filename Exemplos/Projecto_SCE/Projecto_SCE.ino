#include "Arduino.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"


/* Used as a loop counter to create a very crude delay. */
#define mainDELAY_LOOP_COUNT  400000//  ( 0xffffff )

/* The task function. */
void vTaskFunction( void *pvParameters );

/* Define the strings that will be passed in as the task parameters.  These are
  defined const and off the stack to ensure they remain valid when the tasks are
  executing. */
const char *pcTextForTask1 = "EX2: Task 1 is running\r\n";
const char *pcTextForTask2 = "EX2: Task 2 is running\t\n";

/*-----------------------------------------------------------*/

void setup( void )
{
  Serial.begin(115200);
  /* Create one of the two tasks. */
  xTaskCreatePinnedToCore(  &vTaskFunction,      /* Pointer to the function that implements the task. */
                            "Task 1",       /* Text name for the task.  This is to facilitate debugging only. */
                            1024,          /* Stack depth - most small microcontrollers will use much less stack than this. */
                            (void*)pcTextForTask1,  /* Pass the text to be printed in as the task parameter. */
                            1,            /* This task will run at priority 1. */
                            NULL,         /* We are not using the task handle. */
                            1);   /* Core where the task should run */

  /* Create the other task in exactly the same way.  Note this time that we
    are creating the SAME task, but passing in a different parameter.  We are
    creating two instances of a single task implementation. */
  xTaskCreatePinnedToCore( &vTaskFunction, "Task 2", 1024, (void*)pcTextForTask2, 1, NULL, 1);

  /* Start the scheduler so our tasks start executing. */
  //vTaskStartScheduler();

  /* If all is well we will never reach here as the scheduler will now be
    running.  If we do reach here then it is likely that there was insufficient
    heap available for the idle task to be created. */
  //  for( ;; );
  //  return 0;
}
/*-----------------------------------------------------------*/

void vTaskFunction( void *pvParameters )
{
  char *pcTaskName;
  volatile unsigned long ul;

  /* The string to print out is passed in via the parameter.  Cast this to a
    character pointer. */
  pcTaskName = ( char * ) pvParameters;

  /* As per most tasks, this task is implemented in an infinite loop. */
  for ( ;; )
  {
    /* Print out the name of this task. */
    Serial.print( pcTaskName );

    /* Delay for a period. */
    for ( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
    {
      /* This loop is just a very crude delay implementation.  There is
        nothing to do in here.  Later exercises will replace this crude
        loop with a proper delay/sleep function. */
    }
  }
}
//------------------------------------------------------------------------------
void loop()
{
  vTaskDelete( NULL );
}
