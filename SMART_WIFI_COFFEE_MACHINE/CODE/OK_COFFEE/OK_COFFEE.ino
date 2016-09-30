#include "codeArt.h"

#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include "ESP8266_Simple.h"

int dataIn = 5;
int load = 3;
int clock = 4;

#define echopin 8 // Ultrasonic echo pin
#define trigpin 9 // Ultrasonic trigger pin
#define servopin 12 // Servo 
#define force 0 // Force Resisting Sensor

#define ESP8266_SSID  "nope"
#define ESP8266_PASS  "bart1234"

ESP8266_Simple wifi(11, 10);

long duration, distance, pressure;
float value = 0;
float resistance = 0;

Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position
int number, power, timer, currentState;

int strength = 0;
int incomingByte = 0;

int maxInUse = 1;    //change this variable to set how many MAX7219's you'll use

// define max7219 registers
byte max7219_reg_noop        = 0x00;
byte max7219_reg_digit0      = 0x01;
byte max7219_reg_digit1      = 0x02;
byte max7219_reg_digit2      = 0x03;
byte max7219_reg_digit3      = 0x04;
byte max7219_reg_digit4      = 0x05;
byte max7219_reg_digit5      = 0x06;
byte max7219_reg_digit6      = 0x07;
byte max7219_reg_digit7      = 0x08;
byte max7219_reg_decodeMode  = 0x09;
byte max7219_reg_intensity   = 0x0a;
byte max7219_reg_scanLimit   = 0x0b;
byte max7219_reg_shutdown    = 0x0c;
byte max7219_reg_displayTest = 0x0f;

void putByte(byte data)
{
  byte i = 8;
  byte mask;
  while (i > 0)
  {
    mask = 0x01 << (i - 1);      // get bitmask
    digitalWrite( clock, LOW);   // tick
    if (data & mask) digitalWrite(dataIn, HIGH);
    else             digitalWrite(dataIn, LOW);
    digitalWrite(clock, HIGH);   // tock
    --i;                         // move to lesser bit
  }
}

void maxSingle( byte reg, byte col)
{
  digitalWrite(load, LOW);       // begin
  putByte(reg);                  // specify register
  putByte(col);                  // put data
  digitalWrite(load, HIGH);
}

void initMax7219()
{
  //initiation of the max 7219
  maxSingle(max7219_reg_scanLimit, 0x07);
  maxSingle(max7219_reg_decodeMode, 0x00);     // using an led matrix (not digits)
  maxSingle(max7219_reg_shutdown,   0x01);     // not in shutdown mode
  maxSingle(max7219_reg_displayTest, 0x00);    // no display test
  for (int e = 1; e <= 8; e++) maxSingle(e, 0); // empty registers, turn all LEDs off
  maxSingle(max7219_reg_intensity, 0x0f & 0x0f);  // the first 0x0f is the value you can set
}

void setup()
{
  Serial.begin(115200);
  Serial.println("ESP8266 Start");

  pinMode (trigpin, OUTPUT);
  pinMode (echopin, INPUT );
  myservo.attach(servopin);
  pinMode(dataIn, OUTPUT);
  pinMode(clock,  OUTPUT);
  pinMode(load,   OUTPUT);
  initMax7219();
  wifi.begin(9600);
  wifi.setupAsWifiStation(ESP8266_SSID, ESP8266_PASS, &Serial);
  Serial.println();
}

void loop()
{
  // Force Sensor value
  value = analogRead(force);

  // Values for Ultrasonic sensor
  duration = pulseIn (echopin, HIGH);
  digitalWrite(trigpin, LOW);
  digitalWrite(trigpin, HIGH);
  duration = pulseIn (echopin, HIGH);

  // speed of sound in centimeters per second
  distance = duration / 58.2;

  Serial.print("Distance: ");
  Serial.println(distance);

  Serial.print("Pressure: ");
  Serial.println(value, DEC);

  strength = (value / distance);
  if (strength < 10) {
    byte boomArray[] = {0, 0, 0, 0, 0, 0, 64, 0};
    boom(boomArray);
  }
  if (strength >= 10 && strength <= 30) {
    byte boomArray[] = {0, 0, 0, 0, 0, 32, 96, 0};
    boom(boomArray);
  }
  if (strength >= 30 && strength <= 50) {
    byte boomArray[] = {0, 0, 0, 0, 16, 48, 112, 0};
    boom(boomArray);
  }
  if (strength >= 50 && strength <= 70) {
    byte boomArray[] = {0, 0, 0, 8, 24, 56, 120, 0};
    boom(boomArray);
  }
  if (strength >= 70 && strength <= 90) {
    byte boomArray[] = {0, 0, 4, 12, 28, 60, 124, 0};
    boom(boomArray);
  }
  if (strength >= 90) {
    byte boomArray[] = {0, 2, 6, 14, 30, 62, 126, 0};
    boom(boomArray);
  }

  //wifi
  char buffer[250];
  memcpy(buffer, 0, sizeof(buffer));     // Ensure the buffer is empty first!

  strncpy_P(buffer, PSTR("/status"), sizeof(buffer) - 1);

  strncpy_P(buffer + strlen(buffer), PSTR("/"), sizeof(buffer) - strlen(buffer) - 1);
  ltoa(distance, buffer + strlen(buffer), 10); // Note "10" is Base10, not a length

  strncpy_P(buffer + strlen(buffer), PSTR("/"), sizeof(buffer) - strlen(buffer) - 1);
  ltoa(value, buffer + strlen(buffer), 10); // Note "10" is Base10, not a length


  Serial.print("Requesting ");
  Serial.print(buffer);
  Serial.print(": ");

  unsigned int httpResponseCode =
    wifi.GET
    (
      F("54.236.154.35"),     // The IP address of the server you want to contact
      80,                     // The Port to Connect to (80 is the usual "http" port)
      buffer,                 // Your buffer which currently contains the path to request
      sizeof(buffer),         // The size of the buffer
      F("ok-coffee.parseapp.com"), // Optional hostname you are connecting to(* see below)
      0                        // Get from line 2 of the body, no headers (use 0 to get headers)
      // responses often have a leading newline, hence starting
      // from line 2 here, adjust as necessary
    );

  // Now let's interpret the response code
  if (httpResponseCode == 200 || httpResponseCode == ESP8266_OK)
  {
    // Our request was successfull and the response can be found in the buffer
    Serial.println("OK");
    Serial.println(buffer);

    String s = buffer;
    if (s.indexOf("true") > 0 ) {
      Serial.println("true loopje");
      if (/*distance <= 16 && */currentState == 0) {
        currentState = 1;
        for (pos; pos < 180; pos += 1) {
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(5);
        }
      }
    } else {
      Serial.println("false loopje");
      if (/*distance >= 15 && */currentState == 1) {
        currentState = 0;
        for (pos; pos > 0; pos -= 1) {
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(5);
        }
      }
    }
  }
  else
  {
    // Oops, something went wrong.
    if (httpResponseCode < 100)
    {
      // And it's on our end, but what was it?  Well we can find out easily.
      wifi.debugPrintError((byte)httpResponseCode, &Serial);
    }
    else
    {
      // It's probably a server problem
      Serial.print("HTTP Status ");
      Serial.println(httpResponseCode);
    }
  }
  delay (3000);
}

void boom(byte array[])
{
  for (int i = 0; i < 8; i++)
  {
    maxSingle(i + 1, array[i]);
  }
}

