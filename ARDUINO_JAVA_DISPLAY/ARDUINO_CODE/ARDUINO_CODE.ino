char cpnyName[30];
char forename[30];
char surname[30];
char foStudy[30];

void setup() {
  // Start up our serial port, we configured our XBEE devices for 38400 bps.
  Serial.begin(9600);
}

void loop() {
  // handle serial data, if any
  if (Serial.available() > 0) {
    // Company name
    cpnyName[0] = (char)Serial.read();
    Serial.write(cpnyName[0]);

    // forename
    forename[0] = (char)Serial.read();
    Serial.write(forename[0]);

    // surname
    surname[0] = (char)Serial.read();
    Serial.write(surname[0]);

    // field of study
    foStudy[0] = (char)Serial.read();
    Serial.write(foStudy[0]);
    Serial.flush();
  }
}
