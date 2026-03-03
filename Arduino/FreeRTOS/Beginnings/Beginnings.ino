void TaskBlink( void* parameter) {
  pinMode(LED_BUILTIN, OUTPUT);
  for (;;) {
    digitalWrite(LED_BUILTIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(500));
    digitalWrite(LED_BUILTIN, LOW);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}
void setup() {
  xTaskCreate(
    TaskBlink, //Funcion
    "Blink", //Nombre
    2048, //stack size
    NULL, //paramtro
    1, //prioridad
    NULL, // tarea Handle
    1 //core
  );

}

void loop() {
}
