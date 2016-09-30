import processing.serial.*;

Serial myPort;
int A0VAL, A1VAL, LSBA0, MSBA0, LSBA1, MSBA1;
float A0MAP, A1MAP;

void setup() 
{
  size(600, 600);
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
}

void draw()
{
  while ( myPort.available() > 0) {  // If data is available
    LSBA0 = myPort.read();
    MSBA0 = myPort.read();
    LSBA1 = myPort.read(); 
    MSBA1 = myPort.read();
  }
  background(255);
  fill(#002266);
  
  // print values on screen
  text("LSBA0: " + LSBA0, 100, 100);
  text("MSBA0: " + MSBA0, 200, 100);
  text("A0VAL: " + A0VAL, 300, 100);
  text("A0MAP: " + A0MAP, 400, 100);
  text("LSBA1: " + LSBA1, 100, 200);
  text("MSBA1: " + MSBA1, 200, 200);
  text("A1VAL: " + A1VAL, 300, 200);
  text("A1MAP: " + A1MAP, 400, 200);
  
  // convert bytes to ints
  A0VAL = LSBA0 + MSBA0 * 256;
  A1VAL = LSBA1 + MSBA1 * 256;
  
  // map min max values 
  A0MAP = map(A0VAL, 0, 1023, 0, 600 - 100);
  A1MAP = map(A1VAL, 0, 1023, 0, 600 - 100);
  
  rect(0, A0MAP, 25, 100);
  rect(575, A1MAP, 25, 100);
}
