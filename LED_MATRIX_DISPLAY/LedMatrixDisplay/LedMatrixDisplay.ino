//Define start and end pins
const int STARTPIN = 2;
const int ENDPIN = 17;  // pin HIGH9 = A5

void setup()
{
  Serial.begin(9600);
  // Set all pins to output
  for (int iPin = STARTPIN; iPin <= ENDPIN; iPin++)
    pinMode(iPin, OUTPUT);
}

void setPins(byte pinArray[], byte pins[]) {
  for (int iPin = 0; iPin < 8; iPin++)
    digitalWrite(pinArray[iPin], pins[iPin]);
}

void revertedPins(byte pinArray[], byte pins[]) {
  for (int iPin = 0; iPin < 8; iPin++)
    digitalWrite(pinArray[iPin], !pins[iPin]);
}

const int NCOLPINS = 8; // number of columns
const int NROWPINS = 8; // number of rows

int iActiveCol = 0;
byte rowPins[] = {13, 7, 6, 16, 4, 15, 11, 10};
byte colPins[] = {17, 12, 2, 14, 9, 3, 8, 5};


// The image which is drawn consists of an array of 8 bytes
// The individual bits are interpreted as pixels
// Unsigned char bitmap [] = {0x3C, 0x7E, 0xFC, 0xF8, 0xF8, 0xFC, 0x7E, 0x3C};

byte bitmap[8][8] = {
  {HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW},
  {LOW, HIGH, LOW, LOW, LOW, LOW, LOW, LOW},
  {LOW, LOW, HIGH, LOW, LOW, LOW, LOW, LOW},
  {LOW, LOW, LOW, HIGH, LOW, LOW, LOW, LOW},
  {LOW, LOW, LOW, LOW, HIGH, LOW, LOW, LOW},
  {LOW, LOW, LOW, LOW, LOW, HIGH, LOW, LOW},
  {LOW, LOW, LOW, LOW, LOW, LOW, HIGH, LOW},
  {LOW, LOW, LOW, LOW, LOW, LOW, LOW, HIGH}
};

byte invader[8][8] = {
  {LOW, LOW, LOW, HIGH, HIGH, LOW, LOW, LOW},
  {LOW, LOW, HIGH, HIGH, HIGH, HIGH, LOW, LOW},
  {LOW, HIGH, LOW, HIGH, HIGH, LOW, HIGH, LOW},
  {LOW, HIGH, LOW, HIGH, HIGH, LOW, HIGH, LOW},
  {LOW, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW},
  {LOW, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW},
  {HIGH, LOW, HIGH, LOW, LOW, HIGH, LOW, HIGH},
  {HIGH, LOW, LOW, LOW, LOW, LOW, LOW, HIGH}
};

byte zombie[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};


byte lowRow[8] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW };
byte highRow[8] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
int i;

void loop()
{

  setPins(rowPins, lowRow);

  revertedPins(colPins, zombie[i]);
  setPins(rowPins, bitmap[i]);

  i++;
  if (i == 8) {
    i = 0;
  }
  delay(0);
}
