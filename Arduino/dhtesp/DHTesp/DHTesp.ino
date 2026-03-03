#include <DHTesp.h>

DHTesp dht;

#define DHT_PIN 23   // GPIO donde conectás el DHT
#define DHT_TYPE DHTesp::DHT11

void setup() {
  Serial.begin(115200);

  dht.setup(DHT_PIN, DHT_TYPE);

  Serial.println("DHT21 listo");
}

void loop() {
  TempAndHumidity data = dht.getTempAndHumidity();
  float t = data.temperature;
  float h = data.humidity;

  if (!isnan(data.temperature) && !isnan(data.humidity)) {
    Serial.print(t);
    Serial.print(h);
  } else {
    Serial.println("Error leyendo DHT");
  }

  delay(2000);
}
