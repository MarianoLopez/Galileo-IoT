#include "GroveCustomLibrary.h"
const int pinLightSensor = A0;
const int pinSoundSensor = A1;
const int pinTempSensor = A2;
const int pinLed = 4;

GroveTemperature groveTemp = GroveTemperature(pinTempSensor);
GroveLight groveLight = GroveLight(pinLightSensor);
GroveSound groveSound = GroveSound(pinSoundSensor);

boolean ledStatus = false;

void setup() {
  pinMode(pinLed,OUTPUT);
  Serial.begin(9600);
  delay(500);
}

void loop() {
  //Serial.println(groveTemp.getValue());
  Serial.println(groveLight.getValue());
  
  /*Serial.print("temperature = ");
  Serial.println(groveTemp.getValue());
  Serial.print("light = ");
  Serial.println(groveLight.getValue());
  Serial.print("sound intensity = ");
  Serial.println(groveSound.getValue());
  ledStatus= !ledStatus;
  digitalWrite(pinLed,ledStatus);
  Serial.println("**************************************");*/
  delay(1000);
}
