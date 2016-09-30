const  int motor1Pin1 = 8;
const  int motor1Pin2 = 9;
const  int enable1Pin = 10;
const  int motor2Pin1 = 11;
const  int motor2Pin2 = 12;
const  int enable2Pin = 13;
const  int button1Pin = 7;
const  int button2Pin = 6;
const  int button3Pin = 5;
const  int button4Pin = 4;

int button1State = 0;
int button2State = 0;
int button3State = 0;
int button4State = 0;


void setup() {

  // set the motor pins as outputs:

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);

  // set enablePins high so that the motor can turn on:

  digitalWrite(enable1Pin, HIGH);
  digitalWrite(enable2Pin, HIGH);

  // set button pins input

  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(button4Pin, INPUT);
}

void loop() {
  // check the average distance and move accordingly

  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  button3State = digitalRead(button3Pin);
  button4State = digitalRead(button4Pin);


  if (button1State == HIGH) {

    digitalWrite(motor1Pin1, LOW);

    digitalWrite(motor1Pin2, HIGH);

  }

  else if (button3State == HIGH) {

    digitalWrite(motor1Pin1, HIGH);

    digitalWrite(motor1Pin2, LOW);

  }

  else {

    digitalWrite(motor1Pin1, LOW);

    digitalWrite(motor1Pin2, LOW);

  }

  button2State = digitalRead(button2Pin);

  if (button2State == HIGH) {

    digitalWrite(motor2Pin1, LOW);

    digitalWrite(motor2Pin2, HIGH);

  }

  else if (button4State == HIGH) {

    digitalWrite(motor2Pin1, HIGH);

    digitalWrite(motor2Pin2, LOW);

  } klk

  else {

    digitalWrite(motor2Pin1, LOW);

    digitalWrite(motor2Pin2, LOW);

  }
}
