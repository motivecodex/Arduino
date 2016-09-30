// This sketch can be used to find out how
// The LED array is connected to your Arduino

// Define which range of pins are connected to your matrix
const int startPin = 2;
const int endPin = 17;

// Change this value to true if you want to turn on the rows instead of columns
boolean testColumns = true;

// The active pin keeps changing
int activePin = startPin;

void setup()
{
  // Set all pins of the LED matrix OUTPUT
  for (int iPin = startPin; iPin <= endPin; iPin++)
    pinMode(iPin, OUTPUT);

  // The USB port we can see which pin is active and attach it to our perceptions of the LED matrix
  Serial.begin(9600);
  Serial.print("Enter active ");
}

// Function that lets you quickly put all the pins HIGH or LOW
void digitalWriteAll(int mode)
{
  for (int iPin = startPin; iPin <= endPin; iPin++)
    digitalWrite(iPin, mode);
}

byte colPins [] = {255, 255, 255, 255, 255, 255, 255, 255, -1};
byte rowPins [] = {255, 255, 255, 255, 255, 255, 255, 255, -1};

void displayArray(byte array[], char *varName) {
  Serial.print("byte "); Serial.print(varName);
  Serial.print(" [] = {");
  for (int i = 0; i < 7; i++) {
    if (array[i] < 255)
      Serial.print(array[i]);
    Serial.print(",");
  }
  Serial.print(array[7]);
  Serial.println("};");
}

void loop()
{
  if (testColumns)
  {
    // The flow direction will determine which LEDs are to go everything is HIGH and only the active pin is LOW
    digitalWriteAll(HIGH); // Sets all pins HIGH
    digitalWrite(activePin, LOW); // Puts active Pin LOW
  }
  else
  {
    // The flow direction will determine which LEDs are to go everything is LOW and only the active pin is HIGH
    digitalWriteAll(LOW);
    digitalWrite(activePin, HIGH); // Puts active Pin LOW
  }

  Serial.print("Enter active ");
  Serial.print(testColumns ? "column" : "row");
  Serial.print(" (1-8) 0 or 9 nothing happens. Currently active pin:");
  Serial.println(activePin); // Schrijf welke pin actief is

  while (!Serial.available()) {}
  while (Serial.available()) {
    byte selectedRowCol = Serial.parseInt();

    if (selectedRowCol > 0 && selectedRowCol < 9) {
      selectedRowCol--;
      if (testColumns)
        colPins[selectedRowCol] = activePin;
      else
        rowPins[selectedRowCol] = activePin;
    }
  }

  displayArray(rowPins, "rowPins");
  displayArray(colPins, "colPins");

  if (++activePin > endPin) {
    activePin = startPin;
    testColumns = !testColumns;
  }
}


