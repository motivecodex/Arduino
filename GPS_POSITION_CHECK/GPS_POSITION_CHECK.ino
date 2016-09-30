// minimum test code for serial gps

#include <SoftwareSerial.h>

SoftwareSerial gps(3, 4); // RX, TX  Connect GPS TX to pi 3
void setup()
{
  Serial.begin(115200);
  gps.begin(57600);  // may be 4800

}

void loop()
{
  if (gps.available())  Serial.write(gps.read());
}
