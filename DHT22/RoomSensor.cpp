#include "DHT.h"
#include "RoomSensor.h"
#define DHTTYPE DHT22

RoomSensor::RoomSensor() {
}

void RoomSensor::initialize(int moistureSensor, int lightSensor, int DHTPIN) {
  this->moistureSensor = moistureSensor;
  this->lightSensor = lightSensor;
  this->DHTPIN = DHTPIN;
  pinMode(moistureSensor, OUTPUT);
}

int RoomSensor::percentageCalculator(float sensorWaarde, boolean flip) {
  percentage = (sensorWaarde / 1023) * 100;
  if (flip == true) {
    return percentage;
  } else {
    return (100 - percentage);
  }
}

void RoomSensor::readTemp() {
  DHT dht(DHTPIN, DHTTYPE);
  dht.begin();
  temperature = dht.readTemperature();
  Serial.print("Temperature = ");
  Serial.println(temperature);
}

void RoomSensor::readLight() {
  Serial.print("light precentage = ");
  Serial.println(percentageCalculator(analogRead(lightSensor), true));
}

void RoomSensor::readHumidity() {
  DHT dht(DHTPIN, DHTTYPE);
  dht.begin();
  humidity = dht.readHumidity();
  Serial.print("Humidity percentage = ");
  Serial.println(humidity);
}

void RoomSensor::readMoisture() {
  Serial.print("Moisturesensor percentage = ");
  Serial.println(percentageCalculator(analogRead(moistureSensor), false));
}

void RoomSensor::readSensor() {
  DHT dht(DHTPIN, DHTTYPE);
  dht.begin();
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  Serial.print("light precentage = ");
  Serial.println(percentageCalculator(analogRead(lightSensor), true));

  Serial.print("Moisturesensor waarde:");
  Serial.println(percentageCalculator(analogRead(moistureSensor), false));

  Serial.print("Humidity = ");
  Serial.println(humidity);
  Serial.print("Temperature = ");
  Serial.println(temperature);
}


