/***********************************
  ESP32 - ADC Test
  Analog Input ==> ADC_1_0 (GPIO36)

************************************/
#include "Arduino.h"
#define ADC_1_0 36
#define ADC_RESOLUTION 12
#define VREF_PLUS 3.3
#define VREF_MINUS 0.0
int analog_value = 0;
float analog_voltage = 0;
void setup()
{
  Serial.begin(9600);
  analogReadResolution(ADC_RESOLUTION);
  delay(100);
  Serial.println("ESP32 Analog Input ==> ADC_1_0(GPIO36)");
}
void loop()
{
  analog_value = analogRead(ADC_1_0);
  analog_voltage = analog_value * (VREF_PLUS) / (pow (2.0,(float)ADC_RESOLUTION)) + VREF_MINUS;
  Serial.print("ADC_1_0: ");
  Serial.println(analog_value);
  Serial.print("ADC_1_0 VOLT: ");
  Serial.println(analog_voltage);
  delay(500);
}
