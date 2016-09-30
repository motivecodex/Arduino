//We always have to include the library
#include "LedControlMS.h"

/*
  Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
  pin 12 is connected to the DataIn
  pin 11 is connected to the CLK
  pin 10 is connected to LOAD
  We have only a single MAX72XX.
*/
#define NBR_MTX 4
LedControl lc = LedControl(12, 11, 10, NBR_MTX);

long level[8][32] = {
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1}
  , {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1}
  , {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  , {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  , {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  , {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  , {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  , {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};


void setup() {
  /*
    The MAX72XX is in power-saving mode on startup,
    we have to do a wakeup call
  */
  Serial.begin (9600);

  for (int i = 0; i < NBR_MTX; i++) {
    lc.shutdown(i, false);
    /* Set the brightness to a low value */
    lc.setIntensity(i, 1);
    /* and clear the display */
    lc.clearDisplay(i);
  }
  delay(100);
  lc.clearAll();


}

void loop() {
  //   to_leds(level);
  //   lc.clearAll();
  lc.setLed(0, 30, 0, level[0][30]); //board,row,column,state
}

void to_leds(long level[8][32])
{
  int i;
  for (i = 0; i < 7; i++)
  {
    int j;
    for (j = 0; j < 32; j++) {
      if (j < 8) {
        lc.setLed(0, j, i, level[i][j]);
      }
      if (j > 7 && j < 15) {
        lc.setLed(1, (j - 8), i, level[i][j]);
      }
      if (j > 14 && j < 25) {
        lc.setLed(2, (j - 15), i, level[i][j]);
      }
      if (j > 24) {
        lc.setLed(3, (j - 25), i, level[i][j]);
      }
    }
  }
}

