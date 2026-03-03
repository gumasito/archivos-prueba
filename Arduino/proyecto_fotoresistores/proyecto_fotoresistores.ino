int pin = A0;
int val;
int aja;
int pinv = 9;
int pina = 11;
int pinr = 3;
int dtbuzz = 120000;
int pinbuzz = 6;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(pin, INPUT);
  pinMode(pina, OUTPUT);
  pinMode(pinr, OUTPUT);
  pinMode(pinv, OUTPUT);
  pinMode(pinbuzz, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(pin);
  aja = map(val, 0, 1023, 0, 255);
  Serial.println(aja);
  if (aja > 250) {
    analogWrite(pinr, 255);
    analogWrite(pinv, 0);
    digitalWrite(pinbuzz, HIGH);
    delayMicroseconds(dtbuzz);
    digitalWrite(pinbuzz, LOW);
    delayMicroseconds(dtbuzz);
  } else {
    analogWrite(pinr, 0);
    analogWrite(pinv, 255);
    sonidoCorrecto();
    delay(100);

  }
}
void sonidoCorrecto() {
  tone(pinbuzz, 800, 150);
  delay(150);
  tone(pinbuzz, 1000, 150);
  delay(150);
}
