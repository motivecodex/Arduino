#include <SD.h>
String fileName = "json.txt";
File file;
int count = 0;

// dummy data
String plantName = "mint";
int waterLevel = 60;
int degree = 19;

// Arduino UNO
// VCC   = 5V
// GND   = GND
// MISO  = PIN 12
// MOSI  = PIN 11
// SCK   = PIN 13
// CS    = PIN 4

// Arduino MEGA
// VCC   = 5V
// GND   = GND
// MISO  = PIN 50
// MOSI  = PIN 51
// SCK   = PIN 52
// CS    = PIN 53

// pin 53 for MEGA, 4 for UNO
int CS = 53;

void setup()
{
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  Serial.print("Initializing SD card...");
   // pin 53 for MEGA, 4 for UNO
   pinMode(CS, OUTPUT);
   
  if (!SD.begin(CS)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  
  // create file 
  createFile(file, fileName);
  
  // write JSON
  writeFile(file, fileName, plantName, waterLevel, degree);
  
  // read file
  readFile(file, fileName);
}

void loop()
{
  // for loop: write Hello, World 10 times in file
//  for (int i = 0; i < 10; i++){
//    writeFile(file, fileName);
//  }
  // read from file
//  readFile(file, fileName);
//  delay(5000);
}

void createFile(File file, String fileName){
  char charBuf[fileName.length()+1];
  fileName.toCharArray(charBuf, fileName.length()+1);
  
  file = SD.open(charBuf, FILE_WRITE);
  Serial.print("File created: ");
  Serial.println(charBuf);
  file.close();
}

void writeFile(File file, String fileName, String plantName, int waterLevel, int degree){
  char charBuf[fileName.length()+1];
  fileName.toCharArray(charBuf, fileName.length()+1);
  
  file = SD.open(charBuf, FILE_WRITE);
  if (file)
  {    
    file.println("{\"Greenhouse\":");
    file.print("{\"plantName\":\"");
    file.print(plantName);
    file.print("\", ");
    file.print("\"waterLevel\":\"");
    file.print(waterLevel);
    file.print("\", ");
    file.print("\"degree\":\"");
    file.print(degree);
    file.println("\"}");
    file.println("},"); 
    file.close();
  }
  else 
  {
    Serial.println("Error opening file");
  }
  count++;
}

void readFile(File file, String fileName){
  char charBuf[fileName.length()+1];
  fileName.toCharArray(charBuf, fileName.length()+1);
  
  file = SD.open(charBuf);
  if (file) 
  {
    Serial.print("Reading from: ");
    Serial.println(charBuf);
    while (file.available()) {
      Serial.write(file.read());    
    }    
    file.close();
  }
  else 
  {
    Serial.println("Error opening file");
  }
}


