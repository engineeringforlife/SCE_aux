#include "Arduino.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_task_wdt.h"

/* The tasks to be created. */
static void vHandlerTask( void *pvParameters );
static void vPeriodicTask( void *pvParameters );

/* The service routine for the interrupt.  This is the interrupt that the task
  will be synchronized with. */
static void IRAM_ATTR vExampleInterruptHandler( void );

/*-----------------------------------------------------------*/

/* Declare a variable of type SemaphoreHandle_t.  This is used to reference the
  semaphore that is used to synchronize a task with an interrupt. */
SemaphoreHandle_t xCountingSemaphore;

// pin to generate interrupts
const uint8_t interruptPin = 0;


void setup( void )
{
  Serial.begin(115200);
  /* Before a semaphore is used it must be explicitly created.  In this example
    a counting semaphore is created.  The semaphore is created to have a maximum
    count value of 10, and an initial count value of 0. */
  xCountingSemaphore = xSemaphoreCreateCounting( 10, 0 );

  /* Install the interrupt handler. */
  //  _dos_setvect( 0x82, vExampleInterruptHandler );

  pinMode(interruptPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), &vExampleInterruptHandler, RISING);

  /* Check the semaphore was created successfully. */
  if ( xCountingSemaphore != NULL )
  {
    /* Create the 'handler' task.  This is the task that will be synchronized
      with the interrupt.  The handler task is created with a high priority to
      ensure it runs immediately after the interrupt exits.  In this case a
      priority of 3 is chosen. */
    xTaskCreatePinnedToCore( vHandlerTask, "Handler", 1024, NULL, 3, NULL, 1);

    /* Create the task that will periodically generate a software interrupt.
      This is created with a priority below the handler task to ensure it will
      get preempted each time the handler task exist the Blocked state. */
    xTaskCreatePinnedToCore( vPeriodicTask, "Periodic", 1024, NULL, 1, NULL, 1);

    /* Start the scheduler so the created tasks start executing. */
    //vTaskStartScheduler();
  }

  /* If all is well we will never reach here as the scheduler will now be
    running the tasks.  If we do reach here then it is likely that there was
    insufficient heap memory available for a resource to be created. */
  //  for( ;; );
  //  return 0;
}
/*-----------------------------------------------------------*/

static void vHandlerTask( void *pvParameters )
{
  /* As per most tasks, this task is implemented within an infinite loop. */
  for ( ;; )
  {
    /* Use the semaphore to wait for the event.  The semaphore was created
      before the scheduler was started so before this task ran for the first
      time.  The task blocks indefinitely meaning this function call will only
      return once the semaphore has been successfully obtained - so there is no
      need to check the returned value. */
    xSemaphoreTake( xCountingSemaphore, portMAX_DELAY );

    /* To get here the event must have occurred.  Process the event (in this
      case we just print out a message). */
    Serial.print( "EX13: Handler task - Processing event.\r\n" );
  }
}
/*-----------------------------------------------------------*/

static void vPeriodicTask( void *pvParameters )
{
  /* As per most tasks, this task is implemented within an infinite loop. */
  for ( ;; )
  {
    /* This task is just used to 'simulate' an interrupt.  This is done by
      periodically generating a software interrupt. */
    vTaskDelay( 500 / portTICK_PERIOD_MS );

    /* Generate the interrupt, printing a message both before hand and
      afterwards so the sequence of execution is evident from the output. */
    Serial.print( "EX13: Perodic task - About to generate an interrupt.\r\n" );

    digitalWrite(interruptPin, LOW);
    digitalWrite(interruptPin, HIGH);

    Serial.print( "EX13: Periodic task - Interrupt generated.\r\n\r\n\r\n" );
  }
}
/*-----------------------------------------------------------*/

static void IRAM_ATTR vExampleInterruptHandler( void )
{
  static portBASE_TYPE xHigherPriorityTaskWoken;

  xHigherPriorityTaskWoken = pdFALSE;

  /* 'Give' the semaphore multiple times.  The first will unblock the handler
    task, the following 'gives' are to demonstrate that the semaphore latches
    the events to allow the handler task to process them in turn without any
    events getting lost.  This simulates multiple interrupts being taken by the
    processor, even though in this case the events are simulated within a single
    interrupt occurrence.*/
  xSemaphoreGiveFromISR( xCountingSemaphore, (BaseType_t*)&xHigherPriorityTaskWoken );
  xSemaphoreGiveFromISR( xCountingSemaphore, (BaseType_t*)&xHigherPriorityTaskWoken );
  xSemaphoreGiveFromISR( xCountingSemaphore, (BaseType_t*)&xHigherPriorityTaskWoken );

  if ( xHigherPriorityTaskWoken == pdTRUE )
  {
    /* Giving the semaphore unblocked a task, and the priority of the
      unblocked task is higher than the currently running task - force
      a context switch to ensure that the interrupt returns directly to
      the unblocked (higher priority) task.

      NOTE: The syntax for forcing a context switch is different depending
      on the port being used.  Refer to the examples for the port you are
      using for the correct method to use! */
    portYIELD_FROM_ISR();
    //vPortYield();
  }
}
//---------------------------------------------------------------
void loop() {
  vTaskDelete( NULL);
}
