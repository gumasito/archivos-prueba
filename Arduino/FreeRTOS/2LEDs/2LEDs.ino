#define LED1 23
#define LED2 22

TaskHandle_t Task1 = NULL;
TaskHandle_t Task2 = NULL;

void Tarea1 (void* parameter) {
  for (;;) {
    digitalWrite(LED1, HIGH);
    vTaskDelay(pdMS_TO_TICKS(300));
    digitalWrite(LED1, LOW);
    vTaskDelay(pdMS_TO_TICKS(300));
  }
}
void Tarea2 (void* parameter) {
  for (;;) {
    digitalWrite(LED2, HIGH);
    vTaskDelay(pdMS_TO_TICKS(600));
    digitalWrite(LED2, LOW);
    vTaskDelay(pdMS_TO_TICKS(600));
  }
}
void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  xTaskCreatePinnedToCore(
    Tarea1,
    "Tarea1",
    10000,
    NULL,
    1,
    &Task1,
    1
  );
  xTaskCreatePinnedToCore(
    Tarea2,
    "Tarea2",
    10000,
    NULL,
    1,
    &Task2,
    1
  );

}
void loop() {

}
