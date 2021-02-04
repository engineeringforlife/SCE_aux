
#include <Tiny9_LIS2HH12.h>         // Tiny9 LI2HH12TR Library

LIS2HH12 lis = LIS2HH12();
int gravity = 0; //+/-2g = 0, +/- 4g = 2, +/- 8g = 3; 1 is not available
int x,y,z;
//float x1, y1, z1;
void setup() {
  // put your setup code here, to run once:
  lis.powerOn();
  //lis.scale(gravity);
  Serial.begin(9600);                 // Start the serial terminal
  Serial.println("Tiny9 LIS2HH12 Accelerometer Hook Up Guide Example");
  Serial.println();

}

void loop() {
  // put your main code here, to run repeatedly:


  lis.readAccel(&x, &y, &z);

  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.print(", ");
  Serial.println(z);
  //Serial.println(gravity<<4);
  delay(1000);

}




