QueueHandle_t cola;

void TaskProductor(void* p) {
  int valor = 0;
  for (;;) {
    xQueueSend(cola, &valor, portMAX_DELAY);
    valor++;
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void TaskConsumidor(void* p) {
  int recibido;
  for (;;) {
    if (xQueueReceive(cola, &recibido, portMAX_DELAY)) {
      Serial.print("Recibido: ");
      Serial.println(recibido);
    }
  }
}

void setup() {
  Serial.begin(115200);
  cola = xQueueCreate(5, sizeof(int));

  xTaskCreatePinnedToCore(TaskProductor, "Prod", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(TaskConsumidor, "Cons", 2048, NULL, 1, NULL, 1);
}

void loop() {}
