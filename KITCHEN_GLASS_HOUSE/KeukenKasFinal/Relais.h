#ifndef Relais_H
#define Relais_H

#include "Arduino.h"
#include <stdint.h>

class Relais
{
  public:
    Relais();
    void initialize(int, int, int, int, int, int);
    void activate(int);
    void deactivate(int);
    void activateFan();
    void deactivateFan();
    void activateWaterPomp();
    void deactivateWaterPomp();
    void activateAllLights();
    void deactivateAllLights();
    void activateGrowLights();
    void deactivateGrowLights();

  private:
    int fan;
    int waterPomp;
    int farRed;
    int deepRed;
    int blue;
    int white;
};

#endif
