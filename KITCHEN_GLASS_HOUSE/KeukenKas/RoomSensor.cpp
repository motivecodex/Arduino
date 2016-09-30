#include "DHT.h"
#include "Relais.h"
#include "RoomSensor.h"
#include <SD.h>
#define DHTTYPE DHT22

RoomSensor::RoomSensor() {
}

//initializes the roomSensor with 1 extra DHT sensor and a utrasonic sensor.
void RoomSensor::initialize(int moistureSensor1, int moistureSensor2, int lightSensor1, int lightSensor2, int DHTPIN, int DHTPIN2, int waterLevel1, int waterLevel2, int echoPin, int triggerPin) {
  this->moistureSensor1 = moistureSensor1;
  this->moistureSensor2 = moistureSensor2;
  this->lightSensor1 = lightSensor1;
  this->lightSensor2 = lightSensor2;
  this->DHTPIN = DHTPIN;
  this->DHTPIN2 = DHTPIN2;
  this->waterLevel1 = waterLevel1;
  this->waterLevel2 = waterLevel2;
  this->echoPin = echoPin;
  this->triggerPin = triggerPin;

  pinMode(moistureSensor1, INPUT);
  pinMode(moistureSensor2, INPUT);
  pinMode(echoPin, INPUT);
  pinMode(triggerPin, OUTPUT);
}

//Function to calculate the percentage of a sensor value.
//Max sensor value is 1023.
float RoomSensor::percentageCalculator(float sensorWaarde, boolean flip) {
  percentage = (sensorWaarde / 1023) * 100;
  if (flip == true) {
    return percentage;
  } else {
    return (100 - percentage);
  }
}

//reads the light intensity(LUX) and returens how much light in percentage is on
float RoomSensor::readLight1() {
  return percentageCalculator(analogRead(lightSensor1), true);
}

//reads the light intensity(LUX) and returens how much light in percentage is on
float RoomSensor::readLight2() {
  return percentageCalculator(analogRead(lightSensor2), true);
}

//reads the moisture of the ground
float RoomSensor::readMoisture1() {
  return percentageCalculator(analogRead(moistureSensor1), false);
}

//reads the moisture of the ground
float RoomSensor::readMoisture2() {
  return percentageCalculator(analogRead(moistureSensor2), false);
}

//reads the temperature inside the kas
float RoomSensor::readTemp() {
  DHT dht(DHTPIN, DHTTYPE);
  dht.begin();
  temperature = dht.readTemperature();
  return temperature;
}

//reads the humidity inside the kas
float RoomSensor::readHumidity() {
  DHT dht(DHTPIN, DHTTYPE);
  dht.begin();
  humidity = dht.readHumidity();
  return humidity;
}

//reads the humidity outside the kas
float RoomSensor::readHumidityOutside() {
  DHT dht(DHTPIN2, DHTTYPE);
  dht.begin();
  humidity = dht.readHumidity();
  return humidity;
}

//reads the temperature outside the kas
float RoomSensor::readTempOutside() {
  DHT dht(DHTPIN2, DHTTYPE);
  dht.begin();
  temperature = dht.readTemperature();
  return temperature;
}

//calcutes the avarage of a value
float RoomSensor::calculateAvarage(float value, int times) {
  \
  return (value / times);
}

//reads the waterlevel in the containers
int RoomSensor::readWaterLevel(int waterLevelSensor) {
  analogRead(waterLevelSensor);
}

long RoomSensor::readWaterTank() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  duration = pulseIn (echoPin, HIGH);
  distance = duration / 58.2;
  Serial.println(distance);
  return distance;
}

//reads the waterlevel of tray 1
int RoomSensor::readWaterLevel1() {
  return analogRead(waterLevel1);
}

//reads the waterlevel of tray 2
int RoomSensor::readWaterLevel2() {
  return analogRead(waterLevel2);
}

//function to read all the sensor values
void RoomSensor::readSensor(long time) {
  DHT dht(DHTPIN, DHTTYPE);
  DHT dht2(DHTPIN2, DHTTYPE);
  dht.begin();
  dht2.begin();
  temperature = dht.readTemperature();
  temperature2 = dht2.readTemperature();
  humidity = dht.readHumidity();
  humidity2 = dht2.readHumidity();
  startJson();
  printJson("Time", time, true);
  Serial.print("\"");
  Serial.print("waardes");
  Serial.print("\"");
  Serial.print(":");
  startJson();
  printJson("Licht Sensor 1", readLight1(), true);
  printJson("Licht Sensor 2", readLight2(), true);
  printJson("Moisture Sensor 1", readMoisture1(), true);
  printJson("Moisture Sensor 2", readMoisture2(), true);
  printJson("Temperature", temperature, true);
  printJson("Humidity", humidity, true);
  printJson("OutsideTemperature", temperature2, true);
  printJson("OutsideHumidity", humidity2, true);
  printJson("WaterReservoir", readWaterTank(), true);
  printJson("WaterLevel1", readWaterLevel(waterLevel1), true);
  printJson("WaterLevel2", readWaterLevel(waterLevel2), false);
  Serial.println("}");
  closeJson();
}

//function to print in Json the avarage values of the sensores
void RoomSensor::readSensorAvarage(long time, float insideTemp, float insideHumidity, float outsideTemp, float outsideHumidity, float light1, float light2, float moisture1, float moisture2) {
  humidity = insideHumidity;
  temperature = insideTemp;
  humidity2 = outsideHumidity;
  temperature2 = outsideTemp;
  startJson();
  printJson("Time", time, true);
  Serial.print("\"");
  Serial.print("waardes");
  Serial.print("\"");
  Serial.print(":");
  startJson();
  printJson("Licht Sensor 1", light1, true);
  printJson("Licht Sensor 2", light2, true);
  printJson("Moisture Sensor 1", moisture1, true);
  printJson("Moisture Sensor 2", moisture2, true);
  printJson("Temperature", temperature, true);
  printJson("Humidity", humidity, true);
  printJson("OutsideTemperature", temperature2, true);
  printJson("OutsideHumidity", humidity2, true);
  printJson("WaterReservoir", readWaterTank(), true);
  printJson("WaterLevel1", readWaterLevel(waterLevel1), true);
  printJson("WaterLevel2", readWaterLevel(waterLevel2), false);
  Serial.println("}");
  closeJson();
}

//function to open a Json in serial
void RoomSensor::startJson() {
  Serial.println("{");
}

//function to print in Json
void RoomSensor::printJson(String element, float waarde, boolean lastItem) {
  if (lastItem == true) {
    Serial.print("\"");
    Serial.print(element);
    Serial.print("\"");
    Serial.print(": ");
    Serial.print(waarde);
    Serial.println(",");
  }
  else {
    Serial.print("\"");
    Serial.print(element);
    Serial.print("\"");
    Serial.print(": ");
    Serial.println(waarde);
  }
}

//closes the Json in serial
void RoomSensor::closeJson() {
  Serial.println("},");
}

//function that writes to a SD file in json.
void RoomSensor::writeToFile(File sdFile, String fileName, long time, float insideTemp, float insideHumidity, float outsideTemp, float outsideHumidity, float light1, float light2, float moisture1, float moisture2) {
  humidity = insideHumidity;
  temperature = insideTemp;
  humidity2 = outsideHumidity;
  temperature2 = outsideTemp;

  char charBuf[fileName.length() + 1];
  fileName.toCharArray(charBuf, fileName.length() + 1);
  sdFile = SD.open(charBuf, FILE_WRITE);
  // if the file opened okay, write to it:
  if (sdFile) {
    Serial.print("Writing to SD file");
    sdFile.println("{");
    sdFile.print("\"Time\": ");
    sdFile.print(time);
    sdFile.println(",");
    sdFile.print("\"");
    sdFile.print("waardes");
    sdFile.print("\"");
    sdFile.print(":");
    sdFile.println("{");
    sdFile.print("\"LichtSensor1\": ");
    sdFile.print(light1);
    sdFile.println(",");
    sdFile.print("\"LichtSensor2\": ");
    sdFile.print(light2);
    sdFile.println(",");
    sdFile.print("\"MoistureSensor1\": ");
    sdFile.print(moisture1);
    sdFile.println(",");
    sdFile.print("\"MoistureSensor2\": ");
    sdFile.print(moisture2);
    sdFile.println(",");
    sdFile.print("\"Temperature\": ");
    sdFile.print(temperature);
    sdFile.println(",");
    sdFile.print("\"Humidity\": ");
    sdFile.print(humidity);
    sdFile.println(",");
    sdFile.print("\"OutsideTemperature\": ");
    sdFile.print(temperature2);
    sdFile.println(",");
    sdFile.print("\"OutsideHumidity\": ");
    sdFile.print(humidity2);
    sdFile.println(",");
    sdFile.print("\"WaterReservoir\": ");
    sdFile.print(readWaterTank());
    sdFile.println(",");
    sdFile.print("\"WaterLevel1\": ");
    sdFile.print(readWaterLevel(waterLevel1));
    sdFile.println(",");
    sdFile.print("\"WaterLevel2\": ");
    sdFile.println(readWaterLevel(waterLevel2));
    sdFile.println("}");
    sdFile.println("},");
    sdFile.close();
    Serial.println("done.");
  } else {
    Serial.println("error opening SD file");
  }
}

//function that makes a right string of the data to sent to the server.
String RoomSensor::returnDataString(float insideTemp, float insideHumidity, float outsideTemp, float outsideHumidity, float light1, float light2, float moisture1, float moisture2) {
  int moistureValue = moisture1;
  int moistureValue2 = moisture2;
  int lightValue = light1;
  int lightValue2 = light2;
  int humidityValue = insideHumidity;
  int humidityValue2 = outsideHumidity;
  int temperatureValue = insideTemp;
  int temperatureValue2 = outsideTemp;
  int waterReservoir = readWaterTank();
  int waterLevelBak = readWaterLevel(waterLevel1);
  int waterLevelBak2 = readWaterLevel(waterLevel2);
  String dataString = (String(lightValue) + "/" + String(lightValue2) + "/" + String(temperatureValue) + "/" + String(temperatureValue2) + "/" + String(humidityValue) + "/" + String(humidityValue2) + "/" + String(moistureValue) + "/" + String(moistureValue2) + "/" + String(waterReservoir) + "/" + String(waterLevelBak) + "/" + String(waterLevelBak2)).c_str();
  return dataString;
}




