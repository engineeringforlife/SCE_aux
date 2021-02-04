/*******************************************
  ESP32 - TOUCH
  Capacitive Touch input ==> Touch0 (GPIO4)
  Digital pin output ==> GPIO5

********************************************/
#include "Arduino.h"
#define TOUCH_PIN T0
#define LED_PIN 5
int touch_value = 100;
int mediaT0 = 0;
void setup()
{
  Serial.begin(9600);
  delay(100);
  Serial.println("ESP32 Capacitive Touch input ==>Touch0 (GPIO4)");
  pinMode(LED_PIN, OUTPUT);
  digitalWrite (LED_PIN, LOW);
  for (int i = 0; i < 100; i++)
  {
    mediaT0 += touchRead(TOUCH_PIN);
  }
  mediaT0 = mediaT0 / 100;
}
void loop()
{
  touch_value = touchRead(TOUCH_PIN);
  if (touch_value < (mediaT0 * 0.9))
  {
    digitalWrite (LED_PIN, HIGH);
    Serial.print("ON :");
  }
  else
  {
    digitalWrite (LED_PIN, LOW);
    Serial.print("OFF:");
  }
  Serial.print(touch_value);
  Serial.print(" MEDIA:");
  Serial.println(mediaT0);
  delay(100);
}
