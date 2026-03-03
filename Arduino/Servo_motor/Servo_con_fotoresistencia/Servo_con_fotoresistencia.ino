#include <Servo.h>
int resistencia = A0;
int data;
float cambiada;
int motor = 2;
Servo motorsito;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  motorsito.attach(motor);
  pinMode(resistencia, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  data = analogRead(resistencia);
  cambiada = (180. / 422.) * (data - 600.); //formula utilizada para utilizar valores entre los que se encuentre nuestro dispositivo, en este caso es de 1022 y 600
  if (cambiada < 0) cambiada = 0;
  Serial.println(cambiada);
  motorsito.write(cambiada);
  delay(500);
}
