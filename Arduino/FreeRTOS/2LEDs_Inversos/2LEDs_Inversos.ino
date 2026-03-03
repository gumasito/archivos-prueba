#define LED1 23
#define LED2 22

TaskHandle_t Task1 = NULL;
TaskHandle_t Task2 = NULL;

volatile bool encendido = false;

void Tarea1 (void* parameter) {
  for (;;) {
    digitalWrite(LED1, encendido ? HIGH : LOW);
    vTaskDelay(pdMS_TO_TICKS(500));
    encendido = !encendido;
  }
}
void Tarea2 (void* parameter) {
  for (;;) {
    digitalWrite(LED2, encendido ? LOW : HIGH);
    vTaskDelay(pdMS_TO_TICKS(500));
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
    (void*)&encendido,
    1,
    &Task1,
    1
  );
  xTaskCreatePinnedToCore(
    Tarea2,
    "Tarea2",
    10000,
    (void*)&encendido,
    1,
    &Task2,
    1
  );

}
void loop() {

}
