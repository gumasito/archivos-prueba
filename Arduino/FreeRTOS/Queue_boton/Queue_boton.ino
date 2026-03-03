QueueHandle_t cola;
#define LED 23
#define LED2 22
#define BOTON 15

struct COSAS {
  int numero = 0;
};

volatile bool presionado = false;
const uint32_t debounce = 500;
volatile uint32_t lastInterrupt = 0;

void enviar(void* p) {
  COSAS c;
  for (;;) {
    if (presionado) {
      c.numero ++;
      xQueueSend(cola, &c, portMAX_DELAY);
      vTaskDelay(pdMS_TO_TICKS(3000));
      presionado = false;
    }
  }
}
void recibir(void* p) {
  COSAS c;
  for (;;) {
    if (xQueueReceive(cola, &c, portMAX_DELAY)) {
      Serial.println(c.numero);
      if (  c.numero % 2 == 0) {
        digitalWrite(LED, HIGH);
        digitalWrite(LED2, LOW);
      }
      else {
        digitalWrite(LED, LOW);
        digitalWrite(LED2, HIGH);
      }
    }
  }
}
void IRAM_ATTR buttonISR() {
  uint32_t current_time = xTaskGetTickCountFromISR();
  if (current_time - lastInterrupt < pdMS_TO_TICKS(debounce)) {
    return;
  }
  presionado = true;
  lastInterrupt = current_time;
}
void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BOTON, INPUT_PULLUP);
  digitalWrite(LED, LOW);
  digitalWrite(LED2, LOW);

  cola = xQueueCreate(5, sizeof(COSAS));
  attachInterrupt(digitalPinToInterrupt(BOTON), buttonISR, FALLING);

  xTaskCreatePinnedToCore(
    enviar,
    "Enviar",
    4096,
    NULL,
    1,
    NULL,
    1);
  xTaskCreatePinnedToCore(
    recibir,
    "Recibe",
    4096,
    NULL,
    1,
    NULL,
    1);
}
void loop() {

}
