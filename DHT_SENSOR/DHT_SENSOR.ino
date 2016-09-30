#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

float humidity = 0, temperature = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  Serial.print("Humidity = ");
  Serial.println(humidity);
  Serial.print("Temperature = ");
  Serial.println(temperature);
  delay(1000);
}
