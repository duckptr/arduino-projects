#include "DHT.h"

#define DHTPIN 5
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(115200);
  Serial.println("DHT11 test!");
}

void loop() {
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  Serial.print("Humidity:");
  Serial.print(h);
  Serial.print("% ");
  Serial.print("Temperature");
  Serial.print(t);
  Serial.println("℃");
  delay(2000);

}
