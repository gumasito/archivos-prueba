#include <Servo.h>
Servo motor;
int motorPin = 10;
int luz = 3;
int Xpin = A2;
int Ypin = A5;
int pin = 3;
int buzz = 2;
int xVal;
int yVal;
int valorpin;
int datosmotor;
int datosYmotor;
int datosviejos;
int estado = 0;
int brillo;
void setup() {
  // put your setup code here, to run once:
  pinMode(Xpin, INPUT);
  pinMode(Ypin, INPUT);
  pinMode(pin, INPUT_PULLUP);
  pinMode(buzz, OUTPUT);
  pinMode(luz, OUTPUT);
  motor.attach(motorPin);
  Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
  xVal = analogRead(Xpin);
  yVal = analogRead(Ypin);
  valorpin = digitalRead(pin);
  ruid(); //buzzer
  datosmotor = map(xVal, 0, 1023, 0, 180);
  datosYmotor = map (yVal, 0, 1023, 0, 255);
  Serial.println(datosmotor);
  //  if (datosmotor < 91) datosmotor = 91; Para que no baje
  if (datosmotor == 180 && datosviejos == 180) {
    if (estado == 0) {
      motor.write(180);
      estado = 1;
    }
  }
  else if (datosmotor == 0 && datosviejos == 0) {
    if (estado == 1) {
      motor.write(91);
      estado = 0;
    }
  }

  if (datosYmotor > 124) {
    brillo += 10;
    if (brillo > 255) brillo = 255;
    analogWrite(luz, brillo);
  } else if (datosYmotor < 124) {
    brillo -= 10;
    if (brillo < 0) brillo = 0;
    analogWrite(luz, brillo);
  }
  datosviejos = datosmotor;
  delay(200);
}
void ruid() {
  int valor = digitalRead(pin);
  if (valor == 0) {
    tone(buzz, 1000, 500);
    tone(buzz, 800, 300);
    //    digitalWrite(luz,HIGH);
  } else if (brillo == 255 || brillo == 0) {
    tone(buzz, 1500, 500);
    delay(100);
    tone(buzz, 800, 300);

  }
}
