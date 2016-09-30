int lightSensor = A0;
int percentageValue = 0;

int percentageCalculator(float sensorValue, boolean flip) {
  percentageValue = (sensorValue / 1023) * 100;
  if (flip == true) {
    return percentageValue;
  } else {
    return (100 - percentageValue);
  }
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("lightSensor value = ");
  Serial.println(analogRead(lightSensor));
  Serial.print("Light percentage = ");
  Serial.println(percentageCalculator(analogRead(lightSensor), true));
}
