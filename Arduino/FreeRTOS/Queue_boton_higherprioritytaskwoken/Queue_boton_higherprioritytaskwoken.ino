QueueHandle_t cola;
TaskHandle_t Blink;
#define LED 23
#define BOTON 15
volatile uint32_t lastInterrupt = 0;
const uint32_t debounce = 500;

void IRAM_ATTR boton() {
  uint32_t now = xTaskGetTickCountFromISR();
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  if (now - lastInterrupt < pdMS_TO_TICKS(debounce)) {
    return;
  }
  lastInterrupt = now;
  uint32_t evt = 1;
  xQueueSendFromISR(cola, &evt, &xHigherPriorityTaskWoken);
  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
void taskLed(void* p) {
  uint32_t evt;
  for (;;)
    if (xQueueReceive(cola, &evt, portMAX_DELAY)) {
      digitalWrite(LED, !digitalRead(LED));
    }
}
void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BOTON, INPUT_PULLUP);
  cola = xQueueCreate(5, sizeof(uint32_t));
  attachInterrupt(digitalPinToInterrupt(BOTON), boton, FALLING);
  xTaskCreatePinnedToCore(
    taskLed,
    "Led",
    2048,
    NULL,
    1,
    &Blink,
    1);
}
void loop() {
}
