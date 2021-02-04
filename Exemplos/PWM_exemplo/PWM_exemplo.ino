/***********************************************
******
  ESP32 - DAC
  DAC pin output ==> DAC1 (GPIO25)
************************************************
*****/
#include "Arduino.h"
#define DAC1 25
#define DAC_RESOLUTION 8
#define VREF_PLUS 3.3
#define VREF_MINUS 0.0
int DAC1_value = 0;
float DAC1_voltage = 0;
void setup()
{
  Serial.begin(9600);
  delay(100);
  Serial.println("ESP32 DAC pin output ==> DAC1(GPIO25)");
}
void loop()
{
  for (int i = 0; i < 256; i++) {
    DAC1_value = i;
    DAC1_voltage = DAC1_value * (VREF_PLUS-VREF_MINUS) / (pow (2.0,(float)DAC_RESOLUTION)) + VREF_MINUS;
    dacWrite(DAC1, DAC1_value);
    Serial.print(" DAC1_value:");
    Serial.print(DAC1_value);
    Serial.print(" DAC1_voltage:");
    Serial.println(DAC1_voltage);
    delay(100);
  }
}
