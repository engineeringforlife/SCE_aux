#include "Arduino.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include <Wire.h>
#include <rhio-LIS2HH12.h>


#define mainDELAY_LOOP_COUNT    400000 //( 0xffffff )

// SI7006-A20 I2C address is 0x40(64)
#define AddrSI7006 0x40
#define AddrLTR329AL 0x29

#define mainSENDER_1    1
#define mainSENDER_2    2
#define mainSENDER_3    3

char tempComand = 0xF3;
char humComand = 0xF5;





static void vSenderSI7006_HUM( void *pvParameters );
static void vSenderSI7006_TEMP( void *pvParameters );
static void vSenderLTR329ALS01( void *pvParameters );
static void vSenderLIS2HH12( void *pvParameters );
//static void vSenderTask( void *pvParameters );
static void vReceiverTask( void *pvParameters );


/*-----------------------------------------------------------*/

QueueHandle_t xQueue;
typedef struct
{
  float ucValue1;
  float ucValue2;
  float ucValue3;
  float ucSource;
} xData;


static const xData xStructsToSend[ 3 ] =
{
  { 100, 0, 0, mainSENDER_1 }, /* Used by Sender1. */
  { 200, 0, 0, mainSENDER_2 },  /* Used by Sender2. */
  { 203, 0, 0, mainSENDER_3 }
};

LIS2HH12 lis = LIS2HH12();

/* Declare a variable of type SemaphoreHandle_t. This is used to
reference the mutex type semaphore that is used to ensure mutual
exclusive access to stdout. */
SemaphoreHandle_t xMutex;	//=0?




void setup( void )
{
  Serial.begin(115200);
  while(!Serial);



  Wire.begin();

  Wire.begin();
  Wire.beginTransmission(AddrSI7006);
  Wire.endTransmission();
  delay(300);

  Wire.beginTransmission(AddrLTR329AL);
  Wire.write(0x80); //control register
  Wire.write(0x01); //gain=1, active mode
  Wire.endTransmission();
  delay(500);

  lis.begin();
  lis.setBasicConfig();


  xQueue = xQueueCreate( 5, sizeof( xData ) );

  xMutex = xSemaphoreCreateMutex();

  if ( xQueue != NULL )
  {
	  if( xMutex != NULL ){

	  //  xTaskCreatePinnedToCore( vSenderTask, "Sender1", 1024, ( void * ) & ( xStructsToSend[ 0 ] ),2, NULL, 1);
	  //  xTaskCreatePinnedToCore( vSenderTask, "Sender2",   1024, ( void * ) & ( xStructsToSend[ 1 ] ), 2, NULL, 1);
	  //  xTaskCreatePinnedToCore( vSenderSI7006_TEMP, "Sender3", 1024, NULL , 3, NULL, 1);
	      xTaskCreatePinnedToCore( vSenderSI7006_HUM, "Sender4", 1024, NULL, 2, NULL, 1);
	      xTaskCreatePinnedToCore( vSenderSI7006_TEMP, "Sender5", 1024, NULL, 2, NULL, 1);
	      xTaskCreatePinnedToCore( vSenderLTR329ALS01, "Sender6", 2048, NULL, 2, NULL, 1);
	      xTaskCreatePinnedToCore( vSenderLIS2HH12, "Sender7", 2048, NULL, 2, NULL, 1);



	   xTaskCreatePinnedToCore( vReceiverTask, "Receiver", 1024, NULL, 1, NULL, 1);


	   // vTaskStartScheduler();
	  }else{
		  Serial.print( "The mutex not be created.\r\n" );
	  }
  }
  else
  {

	  Serial.print( "The queue not be created.\r\n" );
  }


    //for( ;; );
    //return 0;
}

void loop()
{
  vTaskDelete( NULL );
}


/*-----------------------------------------------------------*/
/*
static void vSenderTask( void *pvParameters )
{
  portBASE_TYPE xStatus;
  const TickType_t xTicksToWait = 500 / portTICK_PERIOD_MS;


  for ( ;; )
  {

    xStatus = xQueueSendToBack( xQueue, pvParameters, xTicksToWait );

    if ( xStatus != pdPASS )
    {

      Serial.print( "EX11: Could not send to the queue.\r\n" );
    }


    taskYIELD();
  }
}
*/


static void vSenderSI7006_HUM( void *pvParameters )
{
  xData xSenderStructure;
  portBASE_TYPE xStatus;
  const TickType_t xTicksToWait = 500 / portTICK_PERIOD_MS;
  float humidity =0.0;
  float temp= 0.0;
  float ctemp = 0.0;
  uint8_t dataT[2] = {0};
  uint8_t dataH[2] = {0};
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
//char* measurementComand;

//  measurementComand = (char*)pvParameters;
  for ( ;; )
  {

	  if( xSemaphoreTake( xMutex, ( 50/portTICK_PERIOD_MS ))){
		  Serial.print( "vSenderSI7006_HUM got access.\r\n" );
		    // Start I2C transmission
		    Wire.beginTransmission(AddrSI7006);
		    // Send HUMIDITY measurement command, NO HOLD MASTER
		    Wire.write(0xF5);
		    // Stop I2C transmission
		    Wire.endTransmission();
		    delay(50);
		    // Request 2 bytes of data
		    Wire.requestFrom(AddrSI7006, 2);
		    // Read 2 bytes of data
		    // humidity msb, humidity lsb
		    if(Wire.available() == 2)
		    {
		      dataH[0] = Wire.read();
		      dataH[1] = Wire.read();
		    }

		    xSemaphoreGive(xMutex);
		    // Convert the data
		    humidity  = ((dataH[0] * 256.0) + dataH[1]);
		    humidity = ((125 * humidity) / 65536.0) - 6;

		    xSenderStructure.ucSource = 3;
		    xSenderStructure.ucValue1 = (float)millis();;

	    xStatus = xQueueSendToBack( xQueue, &xSenderStructure, xTicksToWait );

	    if ( xStatus != pdPASS )
	    {

	      Serial.print( "SI7006_HUM Could not send to the queue.\r\n" );
	    }
	  }else{
		  Serial.print( "vSenderSI7006_HUM couldn't access.\r\n" );
		  }

    vTaskDelayUntil( &xLastWakeTime, ( 1000/portTICK_PERIOD_MS ) );
  }
}



static void vSenderSI7006_TEMP( void *pvParameters )
{
  xData xSenderStructure;
  portBASE_TYPE xStatus;
  const TickType_t xTicksToWait = 500 / portTICK_PERIOD_MS;
  float humidity =0.0;
  float temp= 0.0;
  float ctemp = 0.0;
  uint8_t dataT[2] = {0};
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();


  for ( ;; )
  {

	  if( xSemaphoreTake( xMutex, ( 50/portTICK_PERIOD_MS ))){
		  Serial.print( "vSenderSI7006_TEMP got access.\r\n" );
		    // Start I2C transmission
			Wire.beginTransmission(AddrSI7006);
			// Send temperature measurement command, NO HOLD MASTER
			Wire.write(0xF3);
			// Stop I2C transmission
			Wire.endTransmission();
			delay(50);

			// Request 2 bytes of data
			Wire.requestFrom(AddrSI7006, 2);

			// Read 2 bytes of data
			// temp msb, temp lsb
			if(Wire.available() == 2)
			{
			  dataT[0] = Wire.read();
			  dataT[1] = Wire.read();
			}
			xSemaphoreGive(xMutex);

			// Convert the data
			temp  = ((dataT[0] * 256.0) + dataT[1]);
			ctemp = ((175.72 * temp) / 65536.0) - 46.85;

		    xSenderStructure.ucSource = 4;
		    xSenderStructure.ucValue1 = (float)millis();;

	    xStatus = xQueueSendToBack( xQueue, &xSenderStructure, xTicksToWait );

	    if ( xStatus != pdPASS )
	    {
	      Serial.print( "vSenderSI7006_TEMP could not send to the queue.\r\n" );
	    }
	  }else{
		  Serial.print( "vSenderSI7006_TEMP failed to got access.\r\n" );
	  }
	  vTaskDelayUntil( &xLastWakeTime, ( 1000/portTICK_PERIOD_MS ) );
  }
}


static void vSenderLTR329ALS01( void *pvParameters )
{
  xData xSenderStructure;
  portBASE_TYPE xStatus;
  const TickType_t xTicksToWait = 500 / portTICK_PERIOD_MS;

  byte msb=0, lsb=0;
  uint16_t l;
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();


		  for ( ;; )
		  {
			  if( xSemaphoreTake( xMutex, ( 50/portTICK_PERIOD_MS ))){
					  Serial.print( "vSenderLTR329ALS01 got access.\r\n" );

					  //channel 0
					  Wire.beginTransmission(AddrLTR329AL);
					  Wire.write(0x8A); //low
					  Wire.endTransmission();
					  Wire.requestFrom((uint8_t)AddrLTR329AL, (uint8_t)1);
					  delay(50);
					  if(Wire.available())
						lsb = Wire.read();

					  Wire.beginTransmission(AddrLTR329AL);
					  Wire.write(0x8B); //high
					  Wire.endTransmission();
					  Wire.requestFrom((uint8_t)AddrLTR329AL, (uint8_t)1);
					  delay(50);
					  if(Wire.available())
						msb = Wire.read();
						xSemaphoreGive(xMutex);

					  l = (msb<<8) | lsb;
					  Serial.print( "ABOUT TO PINT CHANNEL OF LTR329ALS01\r\n" );
					  Serial.println(l, DEC); //output in steps (16bit)


					xSenderStructure.ucSource = 5;
					xSenderStructure.ucValue1 = (float)millis();;

					xStatus = xQueueSendToBack( xQueue, &xSenderStructure, xTicksToWait );

					if ( xStatus != pdPASS )
					{
					  Serial.print( "LTR329ALS01 Could not send to the queue.\r\n" );
					}

				}else{
				  Serial.print( "vSenderLTR329ALS01 failed to got access.\r\n" );
				}
			  vTaskDelayUntil( &xLastWakeTime, ( 1000/portTICK_PERIOD_MS ) );
		  }
}



static void vSenderLIS2HH12( void *pvParameters )
{
  xData xSenderStructure;
  portBASE_TYPE xStatus;
  const TickType_t xTicksToWait = 500 / portTICK_PERIOD_MS;
  float x=1, y=2, z=3;
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  for ( ;; )
  {
	  if( xSemaphoreTake( xMutex, ( 50/portTICK_PERIOD_MS ))){
		  Serial.print( "vSenderLIS2HH12 got access.\r\n" );
		    lis.getAccel(&x, &y, &z);
		    xSemaphoreGive(xMutex);
		    xSenderStructure.ucSource = 6;
		    xSenderStructure.ucValue1 = (float)millis();
		    xSenderStructure.ucValue2 = y;
		    xSenderStructure.ucValue3 = z;
	    xStatus = xQueueSendToBack( xQueue, &xSenderStructure, xTicksToWait );
	    if ( xStatus != pdPASS )
	    {
	    	Serial.print( "LIS2HH12 Could not send to the queue.\r\n" );
	    }else{
	    	Serial.print( "LIS2HH12 has sent to the queue.\r\n" );
	    }

	  }else{
		  Serial.print( "vSenderLIS2HH12 failed to got access.\r\n" );
	  }
    vTaskDelayUntil( &xLastWakeTime, ( 1000/portTICK_PERIOD_MS ) );
  }
}


/*-----------------------------------------------------------*/

static void vReceiverTask( void *pvParameters )
{
  xData xReceivedStructure;
  portBASE_TYPE xStatus;

  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  for ( ;; )
  {

		    if ( uxQueueMessagesWaiting( xQueue ) != 5 )
		    {
		      Serial.print( "EX11: Queue should have been full!\r\n" );
		    }

		    xStatus = xQueueReceive( xQueue, &xReceivedStructure, 0 );
		    if ( xStatus == pdPASS )
		    {

		      if ( xReceivedStructure.ucSource == mainSENDER_1 )
		      {
		        //Serial.print( "EX11: From Sender 1 = ");
		        //Serial.println(xReceivedStructure.ucValue);
		      }
		      else if(xReceivedStructure.ucSource == mainSENDER_2)
		      {
		        //Serial.print( "EX11: From Sender 2 = ");
		        //Serial.println( xReceivedStructure.ucValue );
		      }
		      else if (xReceivedStructure.ucSource == 3){
		    	  Serial.print( "****************************\n");
		    	  Serial.print( "Value received from SI7006_HUM : ");
				  Serial.println( xReceivedStructure.ucValue1 );
				  Serial.print( "****************************\n");

		      }else if(xReceivedStructure.ucSource == 4){
		    	  Serial.print( "****************************\n");
		    	  Serial.print( "Value received from SI7006_TEMP : ");
				  Serial.println( xReceivedStructure.ucValue1 );
				  Serial.print( "****************************\n");

		      }else if (xReceivedStructure.ucSource == 5){
		    	  Serial.print( "****************************\n");
		    	  Serial.print( "Value received from LTR: = ");
				  Serial.println( xReceivedStructure.ucValue1 );
				  Serial.print( "****************************\n");
		      }else{
		    	  Serial.print( "****************************\n");
		    	  Serial.print( "Value received from LIS2HH12:\n");
		    	  Serial.print("Received x: ");
		    	  Serial.println(xReceivedStructure.ucValue1, 3);
		    	  Serial.print("Received y: ");
		    	  Serial.println(xReceivedStructure.ucValue2, 3);
		    	  Serial.print("Received z: ");
		    	  Serial.println(xReceivedStructure.ucValue3, 3);
		    	  Serial.print( "****************************\n");
		      }

		    }
		    else
		    {
		      Serial.print( "EX11: Could not receive from the queue.\r\n" );
		    }



    vTaskDelayUntil( &xLastWakeTime, ( 500/portTICK_PERIOD_MS ) );
  }
}

//------------------------------------------------------------------------------
