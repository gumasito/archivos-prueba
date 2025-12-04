int Xpin = A1;
int Ypin = A0;
int pin = 2;
int buzz = 7;
int xVal;
int yVal;
int valorpin;
void setup() {
  // put your setup code here, to run once:
  pinMode(Xpin, INPUT);
  pinMode(Ypin, INPUT);
  pinMode(pin, INPUT_PULLUP);
  pinMode(buzz, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
  xVal = analogRead(Xpin);
  yVal = analogRead(Ypin);
  valorpin = digitalRead(pin);
  Serial.print("Valor de X=");
  Serial.println(xVal);
  Serial.print("Valor de Y=");
  Serial.println(yVal);
  Serial.print("Boton =");
  Serial.println(valorpin);
  ruid();
}
void ruid() {
  int valor = digitalRead(pin);
  if (valor == 0) {
    digitalWrite(buzz, HIGH);
  } else {
    digitalWrite(buzz, LOW);
  }
}
