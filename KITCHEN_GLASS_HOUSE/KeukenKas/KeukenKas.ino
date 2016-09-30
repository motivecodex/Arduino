#include "RoomSensor.h"
#include "Relais.h"
#include "DHT.h"
#include <SD.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(33, 32); // RX, TX
RoomSensor roomSensor;
Relais relais;
File sdFile;
unsigned long time;
int lightTimer = 0;
int dataTimer = 0;
int SDPin = 53;
String dataString = "";
String dataValues = "";
String wifiConnect = "";
String fileName = "sensoren.txt";
float insideTemp = 0;
float insideHumidity = 0;
float outsideTemp = 0;
float outsideHumidity = 0;
float Light1 = 0;
float Light2 = 0;
float moisture1 = 0;
float moisture2 = 0;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  //initializes the relais(fan,waterPomp,farRed,deepRed,blue,white)
  relais.initialize(7, 6, 4, 2, 3, 5);
  //initializes the roomSensor(moistSensor1 Pin, moistSensor2 Pin, LightSensor1 pin, LightSensor2 pin, DHT22Sensor pin, DHT22Sensor2 pin, waterLevel1 pin, waterLevel2 pin, echo pin, trigger pin)
  roomSensor.initialize(A0, A1, A2, A3, 11, 12, A4, A5, 22, 24);
  //configures the Wifi
  wifiConfig("minor_keukenkas", "keukenkas@#");
  //configures the SD-Card Module
  pinMode(SDPin, OUTPUT);
  if (!SD.begin(SDPin)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  //creates a file on the sd card
  createFile(sdFile, fileName);
}

void loop() {
  //opens a serial of pin
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }

  //  test code
  //  roomSensor.readSensor(time);
  //  relais.activateAllLights();
  //  relais.activateGrowLights();
  //  Serial.println(roomSensor.readWaterTank());
  //  Serial.println(roomSensor.readWaterLevel2());

  //function that cares for the plants health. This will activate the waterpomp + fan when needed
  careForPlant();

  delay(1000);
  //for every 1 second delay we increase the data and light timer to make it easier to read the code in seconds
  lightTimer++;
  dataTimer++;

  float temp = roomSensor.readTemp();
  float temp2 = roomSensor.readTempOutside();
  float humidity = roomSensor.readHumidity();
  float humidity2 = roomSensor.readHumidityOutside();

  insideTemp      += temp;
  insideHumidity  += humidity;
  outsideTemp     += temp2;
  outsideHumidity += humidity2;
  Light1          += roomSensor.readLight1();
  Light2          += roomSensor.readLight2();
  moisture1       += roomSensor.readMoisture1();
  moisture2       += roomSensor.readMoisture2();

  //check to activate the growlights every 6 hours
  if (lightTimer <= 57600) {
    relais.activateGrowLights();
  }
  else {
    relais.deactivateGrowLights();
    if (lightTimer >= 86400) {
      lightTimer = 0;
    }
  }

  // writes to the SD-File and server every 10 min
  if (dataTimer >= 600) {
    //    roomSensor.readSensor(time);
    insideTemp = roomSensor.calculateAvarage(insideTemp, dataTimer);
    insideHumidity = roomSensor.calculateAvarage(insideHumidity, dataTimer);
    outsideTemp = roomSensor.calculateAvarage(outsideTemp, dataTimer);
    outsideHumidity = roomSensor.calculateAvarage(outsideHumidity, dataTimer);
    Light1 = roomSensor.calculateAvarage(Light1, dataTimer);
    Light2 = roomSensor.calculateAvarage(Light2, dataTimer);
    moisture1 = roomSensor.calculateAvarage(moisture1, dataTimer);
    moisture2 = roomSensor.calculateAvarage(moisture2, dataTimer);
    time = millis() / 1000;

    Serial.println("write sd");
    roomSensor.writeToFile(sdFile, fileName, time, insideTemp, insideHumidity, outsideTemp, outsideHumidity, Light1, Light2, moisture1, moisture2);
    Serial.println("send data");
    uploadData(insideTemp, insideHumidity, outsideTemp, outsideHumidity, Light1, Light2, moisture1, moisture2);

    dataTimer = 0;

    insideTemp = 0;
    insideHumidity = 0;
    outsideTemp = 0;
    outsideHumidity = 0;
    Light1 = 0;
    Light2 = 0;
    moisture1 = 0;
    moisture2 = 0;
  }

  //  //Sends the data to the server every 10 min
  //  if(dataTimer >= 600){
  //    Serial.println("send data");
  //    uploadData();
  //    dataTimer = 0;
  //  }
}

//Creates a file on the SD card
void createFile(File sdFile, String fileName) {
  char charBuf[fileName.length() + 1];
  fileName.toCharArray(charBuf, fileName.length() + 1);

  sdFile = SD.open(charBuf, FILE_WRITE);
  Serial.print("File created: ");
  Serial.println(charBuf);
  sdFile.close();
}

//function to configure the wifi on the wifi module
void wifiConfig(String ssid, String password) {
  mySerial.write("dofile(\"my.lua\")\n\r");
  // parameters wifiConfig function ssid, password
  wifiConnect = "wifiConfig(\"" + ssid + "\",\"" + password + "\")\n\r";
  mySerial.print(wifiConnect);
  delay(1000);
  mySerial.write("print(wifi.sta.getip())\n\r");
}

//uploads the data to the server
void uploadData(float insideTemp, float insideHumidity, float outsideTemp, float outsideHumidity, float light1, float light2, float moisture1, float moisture2) {
  mySerial.write("dofile(\"my.lua\")\n\r");
  dataValues = roomSensor.returnDataString(insideTemp, insideHumidity, outsideTemp, outsideHumidity, light1, light2, moisture1, moisture2);
  dataString = "setData(\"1/" + dataValues + "\")\n\r";
  mySerial.print(dataString);
  Serial.println(dataString);
}

//function that checks waterlevels,moisture and the humidity and activate the fan or waterpomp if needed
void careForPlant() {
  Serial.print("waterlevel1: ");
  Serial.println(roomSensor.readWaterLevel1());
  Serial.print("waterlevel2: ");
  Serial.println(roomSensor.readWaterLevel2());
  Serial.print("moisture1: ");
  Serial.println(roomSensor.readMoisture1());
  Serial.print("moisture2: ");
  Serial.println(roomSensor.readMoisture2());
  Serial.print("waterTank: ");
  Serial.println(roomSensor.readWaterTank());
  if (roomSensor.readWaterLevel1() == 0 || roomSensor.readWaterLevel2() == 0) {
    relais.deactivateWaterPomp();
    if (roomSensor.readMoisture1() <= 86 || roomSensor.readMoisture2() <= 86) {
      relais.deactivateWaterPomp();
      if (roomSensor.readWaterTank() < 22) {
        relais.activateWaterPomp();
      }
    }
  } else {
    relais.deactivateWaterPomp();
  }

  float humidity = roomSensor.readHumidity();
  float temperatur = roomSensor.readTemp();
  if (humidity >= 85 || temperatur > 24) {
    relais.activateFan();
  } else {
    relais.deactivateFan();
  }
}






