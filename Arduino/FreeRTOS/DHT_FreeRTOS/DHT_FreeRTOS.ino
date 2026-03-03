#include "DHTesp.h"
DHTesp dht;
#define DHTPIN 23
#define DHTTYPE DHTesp::DHT11

QueueHandle_t cola;
TaskHandle_t tarea;
TaskHandle_t sensor;

struct Data {
  float h;
  float t;
};
void Sensor(void* pv) {
  Data datos;
  for (;;) {
    TempAndHumidity data = dht.getTempAndHumidity();
    datos.h = data.humidity;
    datos.t = data.temperature;
    if (!isnan(datos.h) && !isnan(datos.t)) {
      xQueueSend(cola, &datos, portMAX_DELAY);
    }
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}
void Mostrar(void* pv) {
  Data datos;
  for (;;) {
    if (xQueueReceive(cola, &datos, portMAX_DELAY)) {
      Serial.print("Temp: ");
      Serial.println(datos.t);
      Serial.print("Hum: ");
      Serial.println(datos.h);
    }
  }
}
void setup() {
  Serial.begin(115200);
  dht.setup(DHTPIN, DHTTYPE);
  cola = xQueueCreate(5, sizeof(Data));

  xTaskCreatePinnedToCore(
    Mostrar,
    "Display",
    4096,
    NULL,
    1,
    &tarea,
    1);
  xTaskCreatePinnedToCore(
    Sensor,
    "DHT11",
    4096,
    NULL,
    2,
    &sensor,
    0);
}
void loop(){
  
}
