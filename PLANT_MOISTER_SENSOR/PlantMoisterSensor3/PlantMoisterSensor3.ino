int hygroMeter = A0;
int bodemPercentage = 0;

int bodemCalculator(float sensorWaarde) {
  bodemPercentage = (sensorWaarde / 1023) * 100;
  return (100 - bodemPercentage);
}

void setup() {
  Serial.begin(9600);
  pinMode(hygroMeter, INPUT);
}

void loop() {
  Serial.print(" vochtsensor waarde:");
  Serial.println(analogRead(hygroMeter));
  //  Serial.print("precentage =");
  Serial.println(bodemCalculator(analogRead(hygroMeter)));
  delay(1000);
}
