#define LED 3

int brillo = 0;
int direccion = 1;

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  analogWrite(LED, brillo);
  brillo += direccion;
  if (brillo == 0 || brillo == 255) {
    direccion = -direccion;
  }
  delay(10);
}
