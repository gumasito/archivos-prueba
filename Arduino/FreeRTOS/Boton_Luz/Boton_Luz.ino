#define LED 23
#define BOTON 15

TaskHandle_t Prender = NULL;

volatile bool encendido = false;
volatile uint32_t lastInterrupt = 0;
const uint32_t debounceDelay = 400;

void IRAM_ATTR boton_pres() {
  uint32_t current_time = xTaskGetTickCountFromISR();
  if (current_time - lastInterrupt < pdMS_TO_TICKS(debounceDelay)) return;
  lastInterrupt = current_time;

  encendido = !encendido;
}
void prender_luz(void *parametro) {
  bool* estado = (bool*) parametro;

  for (;;) {
    digitalWrite(LED, (*estado) ? HIGH : LOW);
  }
}
void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(BOTON, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(BOTON), boton_pres, FALLING);

  xTaskCreatePinnedToCore(
    prender_luz,
    "Prendiendo Luz",
    10000,
    (void*)&encendido,
    1,
    &Prender,
    1
  );
}
void loop() {
}
