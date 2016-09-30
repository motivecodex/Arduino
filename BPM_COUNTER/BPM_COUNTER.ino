// Max7219 pins
int dataIn = 5;
int load = 3;
int clock = 4;

// bpm
int BUTTON_ONE = 2;
volatile int BUTTON_ONE_STATE = LOW;
float startTime = 0;
float endTime = 0;
float average = 0;
float beats = 0;
int count = 0;

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
  for (int i = 7; i >= 0; i--)
  {
    digitalWrite(clock, LOW);   // tick
    digitalWrite(dataIn, data & (1 << i)); // send bit
    digitalWrite(clock, HIGH);   // tock
  }
}

void maxSingle( byte reg, byte col)
{
  digitalWrite(load, LOW);       // begin
  putByte(reg);                  // specify register
  putByte(col);                  // put data
  digitalWrite(load, HIGH);      // end
}

void initMax7219()
{
  //initiation of the max 7219
  maxSingle(max7219_reg_scanLimit, 0x07);
  maxSingle(max7219_reg_decodeMode, 0x00);  // using an led matrix (not digits)
  maxSingle(max7219_reg_shutdown, 0x01);    // not in shutdown mode
  maxSingle(max7219_reg_displayTest, 0x00); // no display test
  for (int e = 1; e <= 8; e++) maxSingle(e, 0); // empty registers, turn all LEDs off
  maxSingle(max7219_reg_intensity, 0x0f);    // range: 0x00 to 0x0f
}

////////////////////////////////////////////////////////////////////
// This time you get just some basics. Draw one image or clear it.
// In addition we give the number drawing routine. You can have more
// functions and images if you write them yourself or cut them from
// previous sketches. If you want to use codeArt, copy the .h file
// to this directory and include it at the top in this sketch.

void drawImage(byte * image)
{
  for (byte row = 0; row < 8; row++) maxSingle(row + 1, image[row]);
}

void clearImage()
{
  for (byte row = 0; row < 8; row++) maxSingle(row + 1, 0);
}

byte numbers[][10] =  // These numbers are 4x6 pixels
{ {2, 5, 5, 5, 5, 2},  // 0
  {2, 6, 2, 2, 2, 2},  // 1
  {6, 1, 3, 6, 4, 7},  // 2
  {7, 1, 2, 1, 1, 6},  // 3
  {1, 5, 5, 7, 1, 1},  // 4
  {7, 4, 6, 1, 1, 6},  // 5
  {2, 4, 6, 5, 5, 2},  // 6
  {7, 1, 1, 2, 2, 2},  // 7
  {7, 5, 7, 5, 5, 7},  // 8
  {2, 5, 5, 3, 1, 2}
}; // 9

void drawNumber(int number)
{
  int unit    =  number % 10;       // Get the lowest digit
  int decimal = (number / 10) % 10; // Get the second digit
  byte image[8];                    // Reserve memory for the image
  for (int i = 0; i < 6; i++)       // The numbers are only 6 rows tall
  {
    image[i] = numbers[unit][i];    // Just copy the low digit
    if (number > 9)                 // Only draw the high digit if appropriate
    { // Do some bit combining to not overwrite the other digit
      image[i] |= numbers[decimal][i] << 4;
    }
  }
  image[6] = number > 900 ? 128 : 0; // Empty line, or one dot to indicate overflow
  image[7] = 255 >> max(0, 8 - (number / 100)); // every dot represents 100
  drawImage(image);
}

/////////////////////////////////////////////////////////////
// Arduino setup en loop

void setup ()
{
  Serial.begin(9600);

  pinMode(dataIn, OUTPUT);
  pinMode(clock,  OUTPUT);
  pinMode(load,   OUTPUT);

  // PR04
  pinMode(BUTTON_ONE, OUTPUT);
  attachInterrupt(0, bpmCounter, CHANGE);

  initMax7219();
  drawNumber(0);
}

void loop ()
{
  // timer
  //  drawNumber(millis() / 1000);

  // BPM
  digitalWrite(BUTTON_ONE, BUTTON_ONE_STATE);
  drawNumber((int)beats);
  delay(2000);
}

void bpmCounter()
{
  BUTTON_ONE_STATE = !BUTTON_ONE_STATE;
  if (BUTTON_ONE_STATE == HIGH)
  {
    count++;
  }
  if (BUTTON_ONE_STATE == HIGH && count == 1)
  {
    startTime = (millis() / 1000);
  }
  if (BUTTON_ONE_STATE == HIGH && count > 4)
  {
    endTime = (millis() / 1000);
  }
  average = (endTime - startTime) / 60 / count;
  beats = 1 / average;
}
