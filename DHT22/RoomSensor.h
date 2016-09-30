#ifndef RoomSensor_H
#define RoomSensor_H

#include "Arduino.h"
#include <stdint.h>



class RoomSensor
{
  public:
    RoomSensor();
    void initialize(int, int, int);
    int percentageCalculator(float, boolean);
    void readTemp();
    void readLight();
    void readHumidity();
    void readMoisture();
    void readSensor();

  private:
    float humidity;
    float temperature;
    int lightSensor;
    int moistureSensor;
    int percentage;
    int DHTPIN;
};

#endif
