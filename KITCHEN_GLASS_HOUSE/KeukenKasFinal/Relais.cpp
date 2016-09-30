#include "Relais.h"

Relais::Relais() {
}

void Relais::initialize(int fan, int waterPomp, int farRed, int deepRed, int blue, int white) {
  this->fan = fan;
  this->waterPomp = waterPomp;
  this->farRed = farRed;
  this->deepRed = deepRed;
  this->blue = blue;
  this->white = white;
  pinMode(fan, OUTPUT);
  pinMode(waterPomp, OUTPUT);
  pinMode(farRed, OUTPUT);
  pinMode(deepRed, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(white, OUTPUT);
  digitalWrite(waterPomp, HIGH);
  digitalWrite(fan, HIGH);
  digitalWrite(farRed, HIGH);
  digitalWrite(deepRed, HIGH);
  digitalWrite(blue, HIGH);
  digitalWrite(white, HIGH);
}

void Relais::activate(int channel) {
  digitalWrite(channel, LOW);
}

void Relais::deactivate(int channel) {
  digitalWrite(channel, HIGH);
}

void Relais::activateFan() {
  activate(fan);
}

void Relais::deactivateFan() {
  deactivate(fan);
}

void Relais::activateWaterPomp() {
  activate(waterPomp);
}

void Relais::deactivateWaterPomp() {
  deactivate(waterPomp);
}

void Relais::activateAllLights() {
  activate(farRed);
  activate(deepRed);
  activate(blue);
  activate(white);
}

void Relais::deactivateAllLights() {
  deactivate(farRed);
  deactivate(deepRed);
  deactivate(blue);
  deactivate(white);
}

void Relais::activateGrowLights() {
  activate(farRed);
  activate(deepRed);
  activate(blue);
}

void Relais::deactivateGrowLights() {
  deactivate(farRed);
  deactivate(deepRed);
  deactivate(blue);
}
