// Datalogger sketch
//
// Starts logging data to an SD card when a button is pressed
//
// Pins:
//
// SD card MOSI
// SD card MISO
// SD card SCK
// SD card CS

// Status LED
// Button

#include <SD.h>

#define SAMPLE_INTERVAL 10
#define SAMPLES_BETWEEN_BLINK 5
#define LED_PIN 9

const int chipSelect = 10;
File dataFile;
uint16_t msSinceLastSample = 0;
uint32_t elapsedMs = 0;
uint32_t lastMillis = 0;
uint8_t ledState = 0;
uint8_t blinkSamples = 0;

String dataString;
volatile boolean isLogging = false;

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  Serial.print("Initializing SD card...");
  pinMode(10, OUTPUT);
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    while (true) {} // Crash
  }
  Serial.println("card initialized.");

  // Execute "toggleLogging" function when  button is pressed
  attachInterrupt(0, toggleLogging, RISING);
}

// Interrupt handler for button
void toggleLogging() {
  if (!isLogging) { // if we're not currently logging data
    dataFile = SD.open("datalog.txt", FILE_WRITE); // open the file
    if (dataFile) // continue if succeeded
      isLogging = true;
  }
  else { // If we're currently logging data
    dataFile.close(); // close the file
    isLogging = false;
    ledState = false; // reset the LED
    digitalWrite(LED_PIN, ledState);
  }
}

void loop() {
  if (isLogging) {
    elapsedMs = millis(); // toal time that has elapsed at start of loop()
    msSinceLastSample += (elapsedMs - lastMillis); // time elapsed since last sample

    if (msSinceLastSample >= SAMPLE_INTERVAL) {
      dataString = String(elapsedMs % 999); // Store last 3 digits of elapsed time
      dataString += ",";

      // Read analog channels and store the ASCII values in a string
      for (int analogPin = 0; analogPin < 2; analogPin++) {
        int sensor = analogRead(analogPin);
        dataString += String(sensor);
        if (analogPin < 1)
          dataString += ",";
      }

      // Write the string to the file
      if (dataFile) {
        dataFile.println(dataString);
        Serial.println(dataString);
      }
      else {
        Serial.println("error opening datalog.txt");
        while (true) {}
      }

      msSinceLastSample = 0;  // reset the sample timer

      // Handle the LED blinking
      if (++blinkSamples >= SAMPLES_BETWEEN_BLINK) {
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
        blinkSamples = 0;
      }
    }

    lastMillis = millis(); // store elapsed time at the end of loop()
  }
}
