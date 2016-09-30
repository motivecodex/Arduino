#define trigPin 13
#define echoPin 12
const int LED1 = 8;

int sensorValue = 0;

boolean toggle = true;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED1, OUTPUT);
}

void loop() {

  if (Serial.available()) {
    Serial.read();
  }

  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  if (distance >= 200 || distance <= 0) {
    Serial.println("Out of range");
    digitalWrite(LED1, LOW);
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
    digitalWrite(LED1, HIGH);

    sensorValue = Serial.print(distance);;
    digitalWrite(LED1, toggle); // toggle the LED
    toggle = !toggle;
  }
  delay(500);
}
