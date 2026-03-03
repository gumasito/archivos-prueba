#define echo 10
#define trig 11
#define boton 5
#define led 3


bool automatico = false;
float maximo = 0;
float limite = 0;

long data = 0;
float dist = 0;
bool boton_val = false;
bool boton_val_ant = false;
void setup() {
  Serial.begin(115200);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(boton, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  digitalWrite(trig, LOW);
  automatico = true;
}
void Controlar(float distancia) {
  if (dist < distancia - 1) {
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    delay(100);
  } else {
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
  }
}
void loop() {
  boton_val = (digitalRead(boton) == 0);
  if (boton_val && !boton_val_ant) {
    limite = dist;
    automatico = false;
  }
  boton_val_ant = boton_val;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  data = pulseIn(echo, HIGH);
  if (data == 0) return;

  dist = data * 0.034 / 2;
  if (automatico) {
    if (dist > maximo) maximo = dist;
    Controlar(maximo);
  }
  else {
    Controlar(limite);
  }
  Serial.println(dist);
  delay(100);
}
