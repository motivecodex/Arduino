import processing.serial.*;

Serial myPort;
int A0VAL, A1VAL, A2VAL, A3VAL, LSBA0, MSBA0, LSBA1, MSBA1, LSBA2, MSBA2, LSBA3, MSBA3;
float A0MAP, A1MAP, A2MAP, A3MAP;

void setup() 
{
  size(600, 600);
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
}

void draw()
{
  if ( myPort.available() > 0) {  // If data is available
    LSBA0 = myPort.read();
    MSBA0 = myPort.read();
    LSBA1 = myPort.read(); 
    MSBA1 = myPort.read();
    LSBA2 = myPort.read(); 
    MSBA2 = myPort.read();
    LSBA3 = myPort.read(); 
    MSBA3 = myPort.read();
  }
  background(255);
  fill(205);
  
  // convert bytes to ints
  A0VAL = LSBA0 + MSBA0 * 256;
  A1VAL = LSBA1 + MSBA1 * 256;
  A2VAL = LSBA2 + MSBA2 * 256;
  A3VAL = LSBA3 + MSBA3 * 256;
  
  // map min max values 
  A0MAP = map(A0VAL, 0, 1023, 0, 600 - 100);
  A1MAP = map(A1VAL, 0, 1023, 0, 600 - 100);
  A2MAP = map(A2VAL, 0, 1023, 0, 600 - 100);
  A3MAP = map(A3VAL, 0, 1023, 0, 600 - 100);
  
  rect(0, A0MAP, 150, 100);
  rect(150, A1MAP, 150, 100);
  rect(300, A2MAP, 150, 100);
  rect(450, A3MAP, 150, 100);
  delay(200);
}
