#define TOUCH_PIN 4
#define THRESHOLD 40

bool tocado = false;
bool tocado_prev = false;

unsigned long touch_start = 0;
unsigned long last_release = 0;

bool esperando_segundo = false;

void setup() {

}


void loop() {
  int val = touchRead(TOUCH_PIN);
  tocado = (val <= THRESHOLD);

  unsigned long ahora = millis();

  // FLANCO SUBIDA
  if (tocado && !tocado_prev) {
    touch_start = ahora;
  }

  // FLANCO BAJADA
  if (!tocado && tocado_prev) {
    unsigned long duracion = ahora - touch_start;

    if (duracion < 500) {
      Serial.println("TOUCH CORTO");
    } else {
      Serial.println("TOUCH LARGO");
    }

    last_release = ahora;
  }

  tocado_prev = tocado;
}
