/*
  Example sketch for LTR-329ALS-01-Breakout (Digital Light Sensor).
  Board           I2C/TWI Pins
                  SDA, SCL
  ----------------------------
  Uno, Ethernet    A4, A5
  Mega             20, 21
  Leonardo          2,  3
  Due              20, 21
  Example source code free to use.
  Further information: https://learn.watterott.com/license/
*/

#include <Wire.h>

#define I2C_ADDR 0x29

void setup()
{
  Serial.begin(115200);
  while(!Serial); //wait for serial port to connect (needed for Leonardo only)

  Wire.begin();

  Wire.beginTransmission(I2C_ADDR);
  Wire.write(0x80); //control register
  Wire.write(0x01); //gain=1, active mode
  Wire.endTransmission();
  delay(500);
}

void loop()
{
  byte msb=0, lsb=0;
  uint16_t l;

  //channel 1
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(0x88); //low
  Wire.endTransmission();
  Wire.requestFrom((uint8_t)I2C_ADDR, (uint8_t)1);
  delay(1);
  if(Wire.available())
    lsb = Wire.read();

  Wire.beginTransmission(I2C_ADDR);
  Wire.write(0x89); //high
  Wire.endTransmission();
  Wire.requestFrom((uint8_t)I2C_ADDR, (uint8_t)1);
  delay(1);
  if(Wire.available())
    msb = Wire.read();

  l = (msb<<8) | lsb;
  Serial.print( "ABOUT TO PINT CHANNEL 1\r\n" );
  Serial.println(l, DEC); //output in steps (16bit)

  //channel 0
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(0x8A); //low
  Wire.endTransmission();
  Wire.requestFrom((uint8_t)I2C_ADDR, (uint8_t)1);
  delay(1);
  if(Wire.available())
    lsb = Wire.read();

  Wire.beginTransmission(I2C_ADDR);
  Wire.write(0x8B); //high
  Wire.endTransmission();
  Wire.requestFrom((uint8_t)I2C_ADDR, (uint8_t)1);
  delay(1);
  if(Wire.available())
    msb = Wire.read();

  l = (msb<<8) | lsb;
  Serial.print( "ABOUT TO PINT CHANNEL 0\r\n" );
  Serial.println(l, DEC); //output in steps (16bit)

  delay(1000);
}
