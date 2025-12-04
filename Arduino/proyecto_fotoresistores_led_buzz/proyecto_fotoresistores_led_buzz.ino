int valor;
int pin = A0;
int buzz = 6;
int rojo = 3;
int verde = 9;
int blue = 11;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(pin, INPUT);
  pinMode(buzz, OUTPUT);
  pinMode(rojo, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  valor = analogRead(pin);
  int cambio = map(valor, 0, 1023, 0, 255);
  Serial.println(cambio);
  if (cambio > 249) {
    ruido();
  } else if (cambio > 240) {
    ruido_rari();
  } else {
    ruido_tranqui();
  }
}
void ruido() {
  tone(buzz, 1000, 200);
  delay(150);
  analogWrite(verde, 0);
  analogWrite(blue, 0);
  analogWrite(rojo, 255);
}
void ruido_tranqui() {
  tone(buzz, 1500, 200);
  delay(150);
  analogWrite(rojo, 0);
  analogWrite(verde, 255);
  analogWrite(blue,0);
}
void ruido_rari() {
  tone (buzz, 1300, 200);
  delay(150);
  tone(buzz, 1500, 200);
  delay(150);
  analogWrite(rojo, 0);
  analogWrite(verde, 0);
  analogWrite(blue,255);
}
