import processing.serial.*;

// Find out to which port your Arduino is connected
// and replace this number
int portNr = 0;
Serial port = new Serial(this, Serial.list()[portNr], 9600);

void setup()
{
  size(255, 255);
  textSize(32);
  println(Serial.list());
}

int coords = 0;

void draw()
{
  background(0);
  fill(#002266);
  text((mouseX / 32 + 1) + "," + (mouseY / 32 +1) , 100, 100);
  if (pmouseX != mouseX)
  {
    coords = (mouseX / 32) << 4;
    coords += (mouseY / 32);
    println(coords);
    port.write(coords);
  }
}
