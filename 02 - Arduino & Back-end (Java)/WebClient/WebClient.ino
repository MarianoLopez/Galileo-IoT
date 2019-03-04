#include <Ethernet.h>
#include "InetUtils.h"
#include "GroveCustomLibrary.h"

const boolean bridge = true;

const int sleepInMs = 15000;
const int pinLightSensor = A0;
const int pinTempSensor = A2;
GroveTemperature groveTemp = GroveTemperature(pinTempSensor);
GroveLight groveLight = GroveLight(pinLightSensor);

byte mac[] = {  0x98, 0x4F, 0xEE, 0x01, 0x0E, 0x52 };
IPAddress galileo(192,168,1,176);
IPAddress server(192,168,1,3);//back-end

void setup() {
  Serial.begin(9600);
  if(!bridge){
    setupInterfaceName();
    Ethernet.begin(mac,galileo);
    Serial.println("Galileo IP: "+IPAddress2String(Ethernet.localIP())); 
  }
}

void loop(){
  char payload[500];
  sprintf(payload,"{\"device\": \"Galileo\",\"measurements\":[{\"value\": %.2f, \"sensorType\":\"TEMPERATURE\"},{\"value\": %.2f, \"sensorType\":\"LIGHT\"}]}", groveTemp.getValue(),groveLight.getValue());
  httpRequest(server,8080,"POST","/data",payload);
  delay(sleepInMs);
}
