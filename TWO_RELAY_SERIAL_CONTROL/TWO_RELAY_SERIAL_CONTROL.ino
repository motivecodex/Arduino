int thisByte = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Relay control");
  Serial.println("0: off");
  Serial.println("1: for X on");
  Serial.println("2: for X on");
  Serial.println("3: PIN 3 and 4 on");
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    thisByte = Serial.read();
  }

  if (thisByte == 49) {
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  }
  if (thisByte == 50) {
    digitalWrite(4, HIGH);
    digitalWrite(3, LOW);
  }
  if (thisByte == 51) {
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
  }
  if (thisByte == 0 || thisByte == 48) {
    digitalWrite(4, HIGH);
    digitalWrite(3, HIGH);
  }
}
