// Max7219 pins
int dataIn = 5;
int load = 3;
int clock = 4;

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

// game
int BUTTON_PIN = 2;
volatile int BUTTON_STATE = LOW;
int BUTTON_COUNTER = 0;
int stopCount = 0;
#define TRIG_PIN1 13
#define ECHO_PIN1 12
#define TRIG_PIN2 11
#define ECHO_PIN2 10
long DURATION1, DURATION2, DISTANCE1, DISTANCE2;
int PLAYER_ONE_SCORE = 0;
int PLAYER_TWO_SCORE = 0;


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

  initMax7219();
  drawNumber(0);

  // game
  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(0, buttonCounter, CHANGE);
  pinMode(TRIG_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);
  pinMode(TRIG_PIN2, OUTPUT);
  pinMode(ECHO_PIN2, INPUT);
}

void loop ()
{
  // timer
  //  drawNumber(millis() / 1000);

  digitalWrite(BUTTON_PIN, BUTTON_STATE);

  if (BUTTON_COUNTER > 0)
  {
    counter();
    digitalWrite(TRIG_PIN1, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN1, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN1, LOW);
    DURATION1 = pulseIn(ECHO_PIN1, HIGH);
    DISTANCE1 = (DURATION1 / 2) / 29.1;

    digitalWrite(TRIG_PIN2, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN2, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN2, LOW);
    DURATION2 = pulseIn(ECHO_PIN2, HIGH);
    DISTANCE2 = (DURATION2 / 2) / 29.1;

    if (DISTANCE1 < DISTANCE2)
    {
      drawNumber(1);
      PLAYER_ONE_SCORE++;
    }
    if (DISTANCE1 > DISTANCE2)
    {
      drawNumber(2);
      PLAYER_TWO_SCORE++;
    }
    if (PLAYER_ONE_SCORE == 3)
    {
      for (int i = 0; i < 5; i++)
      {
        drawNumber(1);
        delay(500);
        drawNumber(0);
        delay(500);
      }
      PLAYER_ONE_SCORE = 0;
      PLAYER_TWO_SCORE = 0;
    }
    if (PLAYER_TWO_SCORE == 3)
    {
      for (int i = 0; i < 5 ; i++)
      {
        drawNumber(2);
        delay(500);
        drawNumber(0);
        delay(500);
      }
      PLAYER_ONE_SCORE = 0;
      PLAYER_TWO_SCORE = 0;
    }
  }
}

void buttonCounter()
{
  BUTTON_STATE = !BUTTON_STATE;
  if (BUTTON_STATE == HIGH)
  {
    BUTTON_COUNTER++;
    stopCount = 0;
  }
}

void counter() {
  if (BUTTON_COUNTER >= 1 && stopCount <= 0)
  {
    drawNumber(3);
    delay(1000);
    drawNumber(2);
    delay(1000);
    drawNumber(1);
    delay(1000);
    drawNumber(0);
    delay(1000);
    stopCount++;
    BUTTON_COUNTER = 0;
  }
}
