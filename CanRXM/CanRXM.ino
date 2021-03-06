#include "esp32_can.h"
#include "Arduino.h"
#include "SPI.h"
int x=0;

void printFrame(CAN_FRAME *message)
{
  Serial.print(message->id, HEX);
  if (message->extended) Serial.print(" X ");
  else Serial.print(" S ");
  Serial.print(message->length, DEC);
  Serial.print(" ");
  for (int i = 0; i < message->length; i++) {
    Serial.print(message->data.byte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}

void gotHundred(CAN_FRAME *frame)
{
  Serial.print("\nGot special frame!  ");
  //printFrame(frame);
}

void setup() {
  Serial.begin(115200);

  Serial.println("Initializing ...");

  pinMode(GPIO_NUM_16, OUTPUT);
  digitalWrite(GPIO_NUM_16, LOW); //enable CAN transceiver
  // void ESP32CAN::setCANPins(gpio_num_t rxPin, gpio_num_t txPin)
  CAN0.setCANPins(GPIO_NUM_4, GPIO_NUM_5);
  CAN0.begin(500000);

  Serial.println("RECEIVER Ready ...!");

  //CAN0.watchFor(0x0A, 0x0F); //setup a special filter
  CAN0.watchFor(); //then let everything else through anyway
  //CAN0.setCallback(0, gotHundred); //callback on that first special filter
  CAN0.attachCANInterrupt(0, gotHundred);
}

void loop() {
  byte i = 0;
  CAN_FRAME message;
  if (CAN0.read(message)) {
    if (1){
    	Serial.println("id Correspondente!!!");
    	Serial.println("RECEIVED ...!");
    	printFrame(&message);
    	x++;
    	Serial.print(x);
    }
    else
    	Serial.println("id N�o Correspondente!!!");
  }
 // delay(500);
}
