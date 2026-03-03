#define LED1_PIN 2
#define BUTTON_PIN 23

TaskHandle_t BlinkTaskHandle = NULL;

volatile bool taskActive = false;
volatile uint32_t lastInterruptTime = 0;
const uint32_t debounceDelay = 200; // debounce period

void IRAM_ATTR buttonISR() {
  uint32_t currentTime = millis();
  if (currentTime - lastInterruptTime < debounceDelay) {
    return;
  }
  lastInterruptTime = currentTime;

  taskActive = !taskActive;
}

void BlinkTask(void *parameter) {
  bool *enabled = (bool *) parameter;
  for (;;) {
    if (digitalWrite(LED1_PIN, *enabled ? HIGH,LOW);
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Internal pull-up resistor

  xTaskCreatePinnedToCore(
    BlinkTask,         // Task function
    "BlinkTask",       // Task name
    4096,             // Stack size (bytes)
    (void *)&taskActive,              // Parameters
    1,                 // Priority
    &BlinkTaskHandle,  // Task handle
    1                  // Core 1
  );
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);

}

void loop() {
  // Empty because FreeRTOS scheduler runs the task
}
