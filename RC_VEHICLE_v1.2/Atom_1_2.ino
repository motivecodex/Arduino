// Motor pins
const int motor1Pin1 = 8;
const int motor1Pin2 = 9;
const int motor1EnablePin1 = 10;
const int motor2Pin1 = 11;
const int motor2Pin2 = 12;
const int motor2EnablePin2 = 13;

// Bluetooth
char INBYTE;

// void setup
void setup() {

  // Bluetooth connection
  Serial.begin(9600);;

  // Set motor pins as output
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor1EnablePin1, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor2EnablePin2, OUTPUT);

  // enable motor pins
  digitalWrite(motor1EnablePin1, HIGH);
  digitalWrite(motor2EnablePin2, HIGH);

}

// void loop
void loop() {

  while (!Serial.available()); // stay here so long as COM port is empty
  INBYTE = Serial.read(); // read next available byte

  // Tank control
  // w = forward, s = backwards, a = left, d = right, x = stop, 0 = autonomous
  if ( INBYTE == 'w' )
  {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
    Serial.println("forward");
  }
  else if ( INBYTE == 'a' )
  {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
    Serial.println("left");
  }
  else if ( INBYTE == 'd' )
  {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
    Serial.println("right");
  }
  else if ( INBYTE == 's' )
  {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
    Serial.println("backwards");
  }
  else if ( INBYTE == 'x' )
  {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
    Serial.println("stop");
  }
}
