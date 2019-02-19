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
  system("ifconfig enp0s20f6 192.168.0.30 netmask 255.255.255.0 &>/dev/ttyGS0 &");
  system("ifconfig &>/dev/ttyGS0 &");
  delay(500);
}

void loop() {
  Serial.print("temperature = ");
  Serial.println(groveTemp.getValue());
  Serial.print("light = ");
  Serial.println(groveLight.getValue());
  Serial.print("sound intensity = ");
  Serial.println(groveSound.getValue());
  ledStatus= !ledStatus;
  digitalWrite(pinLed,ledStatus);
  Serial.println("**************************************");
  delay(1000);
}
