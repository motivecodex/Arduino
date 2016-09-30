/*Circuit:
  10 KOhms resistor between digital 2 and analog 0

        digital 2---*
                  |
                  \
                  /
                  \ R1
                  /
                  |
                  |
        analog 0----*
                  |
                  |
                   ----> nail 1

                   ----> nail 2
                  |
                  |
                  |
        digital 3---*
*/


#define moisture_input 0
#define divider_top 2
#define divider_bottom 3

int ledGreen = 13;
int ledOrange = 12;
int ledRed = 11;

int moisture; // analogical value obtained

int SoilMoisture() {
  int reading;
  // set driver pins to outputs
  pinMode(divider_top, OUTPUT);
  pinMode(divider_bottom, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledOrange, OUTPUT);
  pinMode(ledRed, OUTPUT);

  // drive a current through the divider in one direction
  digitalWrite(divider_top, LOW);
  digitalWrite(divider_bottom, HIGH);

  // wait a moment for capacitance effects to settle
  delay(1000);

  // take a reading
  reading = analogRead(moisture_input);

  // reverse the current
  digitalWrite(divider_top, HIGH);
  digitalWrite(divider_bottom, LOW);

  // give as much time in 'reverse' as in 'forward'
  delay(1000);

  // stop the current
  digitalWrite(divider_bottom, LOW);

  return reading;
}


void setup () {
  Serial.begin(9600);

}

void loop (void) {
  moisture = SoilMoisture(); // assign the result of SoilMoisture() to the global variable 'moisture'

  /*
    moisture=SoilMoisture(); // assign the result of SoilMoisture() to the global variable 'moisture'
    Serial.print("Soil moisture: ");
    Serial.print(moisture); // print the analogical measurement of the experiment
    // later i will improve here a calculation for derive Soil Moisture in %
    Serial.println();
    delay(1000);
  */

  if (moisture < 12)
  {
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledOrange, LOW);
    digitalWrite(ledRed, HIGH);
    Serial.print("Soil moisture: ");
    Serial.print(moisture);
    Serial.print(": Water the poor plant!");
    Serial.println();
  } else if (moisture >= 12 && moisture < 25)
  {
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledOrange, HIGH);
    digitalWrite(ledRed, LOW);
    Serial.print("Soil moisture: ");
    Serial.print(moisture);
    Serial.print(": Plant almost needs watering");
    Serial.println();
  } else if (moisture >= 25 && moisture < 30)
  {
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledOrange, LOW);
    digitalWrite(ledRed, LOW);
    Serial.print("Soil moisture: ");
    Serial.print(moisture);
    Serial.print(" Plant has enough water");
    Serial.println();
  } else if (moisture >= 30)
  {
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledOrange, LOW);
    digitalWrite(ledRed, HIGH);
    delay(500);
    digitalWrite(ledRed, LOW);
    Serial.print("Soil moisture: ");
    Serial.print(moisture);
    Serial.print(": Overwatering");
    Serial.println();
  }
  delay(1000);
}
