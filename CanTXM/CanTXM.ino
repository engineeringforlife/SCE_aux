#include "Arduino.h"
#include <esp32_can.h>
#include <SPI.h>

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
  Serial.print("Got special frame!  ");
  printFrame(frame);
}

void setup() {
  Serial.begin(115200);

  Serial.println("Initializing ...");

  pinMode(GPIO_NUM_16, OUTPUT);
  digitalWrite(GPIO_NUM_16, LOW); //enable CAN transceiver
  // void ESP32CAN::setCANPins(gpio_num_t rxPin, gpio_num_t txPin)
  CAN0.setCANPins(GPIO_NUM_4, GPIO_NUM_5);
  CAN0.begin(500000);

  Serial.println("SENDER Ready ...!");

}

void loop() {

  //or, just plain send traffic periodically
	int temperatura = 0x55;
  CAN_FRAME txFrame;
  txFrame.rtr = 0;
  txFrame.id = 0x02;
  txFrame.extended = false;
  txFrame.length = 4;
  txFrame.data.uint8[0] = temperatura;
  txFrame.data.uint8[1] = 0x1A;
  txFrame.data.uint8[2] = 0xFF;
  txFrame.data.uint8[3] = 0x5D;

  Serial.println("SENT ...!");
  CAN0.sendFrame(txFrame);
  delay(50);
  /*   message.id++;
     message.length = 8;
     for(i=0;i<message.length;i++) {
      message.data.uint8[i]++;
     }
     CAN.sendFrame(message);
  */
}
