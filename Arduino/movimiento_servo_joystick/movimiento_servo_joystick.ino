#include <Servo.h>
Servo motor;
int pinmotor = 8;
int Xpin = A0;
int Ypin = A1;
int pin = 7;
int buzz = 6;
int xVal;
int yVal;
int valorpin;
int datosmotor;
void setup() {
  // put your setup code here, to run once:
  pinMode(Xpin, INPUT);
  pinMode(Ypin, INPUT);
  pinMode(pin, INPUT_PULLUP);
  pinMode(buzz, OUTPUT);
  motor.attach(pinmotor);
  Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
  xVal = analogRead(Xpin);
  yVal = analogRead(Ypin);
  valorpin = digitalRead(pin);
  ruid(); //buzzer
  datosmotor = map(xVal,0,1023,0,180);
  Serial.println(datosmotor);
  motor.write(datosmotor);
  delay(10);
}
void ruid() {
  int valor = digitalRead(pin);
  if (valor == 0) {
    digitalWrite(buzz, HIGH);
  } else {
    digitalWrite(buzz, LOW);
  }
}
