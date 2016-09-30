#include "RoomSensor.h"
RoomSensor roomSensor;

void setup() {
  Serial.begin(9600);
  //initializes the roomSensor(moistSensor Pin, LightSensor pin, DHT22Sensor pin)
  roomSensor.initialize(A0, A1, 2);
}

void loop() {
  roomSensor.readSensor();
  delay(1000);
}
