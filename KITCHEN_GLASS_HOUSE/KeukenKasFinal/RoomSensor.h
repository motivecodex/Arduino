#ifndef RoomSensor_H
#define RoomSensor_H

#include "Arduino.h"
#include "Relais.h"
#include <SD.h>
#include <stdint.h>

class RoomSensor
{
  public:
    RoomSensor();
    void initialize(int, int, int, int, int, int, int, int, int, int);
    float percentageCalculator(float, boolean);
    float readLight1();
    float readLight2();
    float readMoisture1();
    float readMoisture2();
    float readHumidity();
    float readTemp();
    float readTempOutside();
    float readHumidityOutside();
    float calculateAvarage(float, int);
    long readWaterTank();
    int readWaterLevel(int);
    int readWaterLevel1();
    int readWaterLevel2();
    void readSensor(long);
    void readSensorAvarage(long, float, float, float, float, float, float, float, float);
    void startJson();
    void printJson(String, float, boolean);
    void closeJson();
    void writeToFile(File, String, long, float, float, float, float, float, float, float, float);
    String returnDataString(float, float, float, float, float, float, float, float);

  private:
    float humidity;
    float temperature;
    float humidity2;
    float temperature2;
    float percentage;
    int lightSensor1;
    int lightSensor2;
    int moistureSensor1;
    int moistureSensor2;
    int DHTPIN;
    int DHTPIN2;
    int waterLevel1;
    int waterLevel2;
    int echoPin;
    int triggerPin;
    long distance;
    long duration;
};

#endif
