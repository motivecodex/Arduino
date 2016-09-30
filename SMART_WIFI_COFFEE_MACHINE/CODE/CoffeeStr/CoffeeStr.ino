#include "codeArt.h"

int dataIn = 2;
int load = 3;
int clock = 4;

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

void setup ()
{
  Serial.begin(9600);
  pinMode(dataIn, OUTPUT);
  pinMode(clock,  OUTPUT);
  pinMode(load,   OUTPUT);
  initMax7219();
}

void loop ()
{
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    if (incomingByte == 49) {
      byte boomArray[] = {0, 0, 0, 0, 0, 0, 64, 0};
      boom(boomArray);
    }
    if (incomingByte == 50) {
      byte boomArray[] = {0, 0, 0, 0, 0, 32, 96, 0};
      boom(boomArray);
    }
    if (incomingByte == 51) {
      byte boomArray[] = {0, 0, 0, 0, 16, 48, 112, 0};
      boom(boomArray);
    }
    if (incomingByte == 52) {
      byte boomArray[] = {0, 0, 0, 8, 24, 56, 120, 0};
      boom(boomArray);
    }
    if (incomingByte == 53) {
      byte boomArray[] = {0, 0, 4, 12, 28, 60, 124, 0};
      boom(boomArray);
    }
    if (incomingByte == 54) {
      byte boomArray[] = {0, 2, 6, 14, 30, 62, 126, 0};
      boom(boomArray);
    }

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
}

void boom(byte array[])
{
  for (int i = 0; i < 8; i++)
  {
    maxSingle(i + 1, array[i]);
  }
}
