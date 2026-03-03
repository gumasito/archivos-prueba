#define TOUCH_PIN 4
#define LED 23

bool estado = false;
unsigned long tiempo = 0;
bool tocado = false;
bool tocado_dsp = false;
void setup() {
  Serial.begin(115200);
}

void loop() {
  int val = touchRead(TOUCH_PIN);
  if (millis() - tiempo < 400) {
    return;
  }
  tiempo = millis();
  tocado = (val <= 40);
  if (tocado && !tocado_dsp){
    estado = !estado;
    digitalWrite(LED, estado ? HIGH: LOW);
  }
  tocado_dsp = tocado;
}
