#include "Test.h"

Test test;

// defines baud
#define BAUD (9600)

// defines pins numbers
const int stepPin = 3;
const int dirPin = 4;
const int enable = 5;

// other constants and non-constants
int x;
const String instructions = "Commands: \n\n unlock || u \n lock || l\n";
const String longLine = "----------------------------------------------------------------";

// serial read in data
char inData[20]; // Allocate some space for the string
char inChar = -1; // Where to store the character read
byte index = 0; // Index into array; where to store the character

void setup()
{
  // baud
  Serial.begin(BAUD);

  // setup pins
  pinMode(enable, OUTPUT); // Enable
  pinMode(stepPin, OUTPUT); // Step
  pinMode(dirPin, OUTPUT); // Dir
  digitalWrite(enable, LOW);
  digitalWrite(stepPin, LOW);
  digitalWrite(dirPin, LOW);

  // other commands
  Serial.println(instructions);
  Serial.println(longLine);
}

// read serial into string
char Comp(char* This) {
  while (Serial.available() > 0) // Don't read unless
    // you know there is data
  {
    if (index < 19) // One less than the size of the array
    {
      inChar = Serial.read(); // Read a character
      inData[index] = inChar; // Store it
      index++; // Increment where to write next
      inData[index] = '\0'; // Null terminate the string
    }
  }

  if (strcmp(inData, This)  == 0) {
    for (int i = 0; i < 19; i++) {
      inData[i] = 0;
    }
    index = 0;
    return (0);
  }
  else {
    return (1);
  }
}

void loop()
{
  if (Comp("unlock") == 0) {
    Serial.write("Unlocking\n");
    unlock();
  }
  if (Comp("lock") == 0) {
    Serial.write("Locking\n");
    lock();
  }
  if (Comp("test") == 0) {
    Serial.write("Locking\n");
    test.test();
  }
}

// <-- UNLOCK -->
void unlock() {
  digitalWrite(dirPin, HIGH); // Set Dir high
  for (x = 0; x < 2325; x++) // Loop 200 times
  {
    digitalWrite(stepPin, HIGH); // Output high
    delay(1); // Wait
    digitalWrite(stepPin, LOW); // Output low
    delay(1); // Wait
  }
  Serial.println("Unlocked\n");
}

// <-- LOCK -->
void lock() {
  digitalWrite(dirPin, LOW); // Set Dir high
  for (x = 0; x < 2325; x++) // Loop 200 times
  {
    digitalWrite(stepPin, HIGH); // Output high
    delay(1); // Wait
    digitalWrite(stepPin, LOW); // Output low
    delay(1); // Wait
  }
  Serial.println("Locked\n");
}
