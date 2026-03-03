#define LED1 23
#define LED2 22
TaskHandle_t TaskLed;
TaskHandle_t TaskLed2;

SemaphoreHandle_t serialMutex;

void BlinkLed1(void* parameter) {
  for (;;) {
    if (xSemaphoreTake(serialMutex, portMAX_DELAY)) {
      Serial.println("Task A escribiendo");
      digitalWrite(LED1, HIGH);
      vTaskDelay(pdMS_TO_TICKS(500));
      digitalWrite(LED1, LOW);
      vTaskDelay(pdMS_TO_TICKS(500));
      xSemaphoreGive(serialMutex);
    }
    vTaskDelay(pdMS_TO_TICKS(200));
  }
}
void BlinkLed2(void* parameter) {
  for (;;) {
    if (xSemaphoreTake(serialMutex, portMAX_DELAY)) {
      Serial.println("Task B escribiendo");
      digitalWrite(LED2, HIGH);
      vTaskDelay(pdMS_TO_TICKS(1000));
      digitalWrite(LED2, LOW);
      vTaskDelay(pdMS_TO_TICKS(1000));
      xSemaphoreGive(serialMutex);
    }
    vTaskDelay(pdMS_TO_TICKS(200));
  }
}
void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  serialMutex = xSemaphoreCreateMutex();

  xTaskCreatePinnedToCore(
    BlinkLed1,
    "Led1",
    4096,
    NULL,
    5,
    &TaskLed,
    0);
  xTaskCreatePinnedToCore(
    BlinkLed2,
    "Led2",
    4096,
    NULL,
    0,
    &TaskLed2,
    0);
}

void loop() {

}
