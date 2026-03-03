QueueHandle_t cmdQueue;

struct Comando {
  int tipo;
};

void TaskInput(void* p) {
  Comando c;
  for (;;) {
    c.tipo = 1;
    xQueueSend(cmdQueue, &c, portMAX_DELAY);
    vTaskDelay(pdMS_TO_TICKS(3000));
  }
}

void TaskLogic(void* p) {
  Comando c;
  for (;;) {
    if (xQueueReceive(cmdQueue, &c, portMAX_DELAY)) {
      if (c.tipo == 1) {
        Serial.println("Acción ejecutada");
      }
    }
  }
}

void setup() {
  Serial.begin(115200);
  cmdQueue = xQueueCreate(5, sizeof(Comando));

  xTaskCreatePinnedToCore(TaskInput, "Input", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(TaskLogic, "Logic", 2048, NULL, 1, NULL, 1);
}

void loop() {}
