#include "rhio-LIS2HH12.h"
#include "wire.h"
#include <BLEDevice.h>

LIS2HH12 lis = LIS2HH12();
int gravity = 0; //+/-2g = 0, +/- 4g = 2, +/- 8g = 3; 1 is not available
int x,y,z; 
float x11, y11, z11;
void setup() {
  // put your setup code here, to run once:
  //lis.powerOn();
  //lis.scale(gravity);
  Serial.begin(9600);                 // Start the serial terminal
  Serial.println("Tiny9 LIS2HH12 Accelerometer Hook Up Guide Example");
  Serial.println();
  
}

void loop() {
  // put your main code here, to run repeatedly:
    
  
  lis.readAccel(&x, &y, &z); 
  scale();
  Serial.print(x11);
  Serial.print(", ");
  Serial.print(y11);
  Serial.print(", ");
  Serial.println(z11);
  //Serial.println(gravity<<4);
  delay(1000);
  
}

void scale(){
  if(gravity == 2){
      x11 = (float)x*0.000244;
      y11 = (float)y*0.000244;
      z11 = (float)z*0.000244;
  }
  else if(gravity == 1){
      x11 = (float)x*0.000122;
      y11 = (float)y*0.000122;
      z11 = (float)z*0.000122;
  }
  else{
      x11 = (float)x*0.000061;
      y11 = (float)y*0.000061;
      z11 = (float)z*0.000061;
  }  
}

