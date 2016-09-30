
// to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int LED1 = 3; // Analog output pin that the LED is attached to
const int LED2 = 4;
const int LED3 = 5;

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value:

  if (sensorValue > 400) {

    digitalWrite(LED1, HIGH);
    // print the results to the serial monitor:
    Serial.print("sensor = GREEN = " );
    Serial.println(sensorValue);
    // Serial.print("\t output = ");
    // Serial.println(outputValue);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);

  } else if (sensorValue > 200 && sensorValue < 400) {

    digitalWrite(LED2, HIGH);
    // print the results to the serial monitor:
    Serial.print("sensor = ORANGE = " );
    Serial.println(sensorValue);
    digitalWrite(LED1, LOW);
    digitalWrite(LED3, LOW);

  } else if (sensorValue < 200 ) {

    digitalWrite(LED3, HIGH);
    // print the results to the serial monitor:
    Serial.print("sensor = RED = " );
    Serial.println(sensorValue);

    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  }


  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);
}
