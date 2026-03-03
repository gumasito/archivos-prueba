#include <SoftwareSerial.h>
//#include "BluetoothSerial.h"
//BluetoothSerial BT;
SoftwareSerial BT(11, 10); //RX TX

unsigned long tiempo = 0;
bool acelerando = false;
bool frenando = false;
bool retrocediendo = false;
// Pines del L298N
#define IN1 9//32
#define IN2 8//33 //8
#define ENA 6//35 // 6

#define LED 12 //12
#define LED_B 13 //13

#define IN3 3//26 //3
#define IN4 2//27 //2
#define ENB 5//14 //5

#define BUZZ 4

int velocidad = 100;
int velocidadMax = 255;

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  Serial.println("Bluetooth listo. Conectate al dispositivo ESP32_Motor");

  pinMode(LED, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {
  if (BT.available()) {
    //String comando = BT.readStringUntil('\n');
    //comando.trim();
    char comando = BT.read();
    Serial.println(comando);

    if (comando == 'F') {   // Adelante
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      acelerando = true;
      frenando = false;
      analogWrite(ENA, velocidad);
      analogWrite(ENB, velocidad);
      digitalWrite(LED_B, LOW);
    }
    else if (comando == 'S') { // Soltar acelerador → espera antes de frenar
      acelerando = false;
      digitalWrite(LED_B, HIGH);
      retrocediendo = true;
      tiempo = millis();
    }
    else if (retrocediendo && comando != 'S') {
      retrocediendo = false;
    }
    else if (comando == 'R') { // Giro derecha
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      acelerando = true;
      frenando = false;
      analogWrite(ENA, 150);
      analogWrite(ENB, 0);
      digitalWrite(LED_B, LOW);
    }
    else if (comando == 'L') { // Giro izquierda
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(ENB, 150);
      analogWrite(ENA, 0);
      digitalWrite(LED_B, LOW);
      acelerando = true;
      frenando = false;
    }
    else if (comando == 'H') {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(ENB, velocidad / 2);
      analogWrite(ENA, velocidad);
      acelerando = true;
      frenando = false;
      digitalWrite(LED_B, LOW);

    }
    else if (comando == 'G') {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(ENA, velocidad / 2);
      analogWrite(ENB, velocidad);
      acelerando = true;
      frenando = false;
      digitalWrite(LED_B, LOW);
    }
    else if (comando == 'B') { // Atrás
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      velocidad = 150;
      acelerando = true;
      frenando = false;
      analogWrite(ENA, velocidad);
      analogWrite(ENB, velocidad);
      digitalWrite(LED_B, LOW);
    }
    else if (comando == 'I') {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      velocidad = 150;
      analogWrite(ENA, velocidad / 2);
      acelerando = true;
      frenando = false;
    }
    else if (comando == 'J') {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      velocidad = 150;
      analogWrite(ENB, velocidad / 2);
      acelerando = true;
      frenando = false;
    }
    else if (comando == 'Y') {
      sonar_bocina();
    }
    else if (comando == 'U') {
      digitalWrite(LED, HIGH);
    }
    else if (comando == 'u') {
      digitalWrite(LED, LOW);
    }
    else if (comando == 'Z') {
      aumentarMarcha();
      analogWrite(ENA, velocidad);
      analogWrite(ENB, velocidad);
    }
  }

  // --- CONTROL DE FRENO AUTOMÁTICO ---
  if (!acelerando && (millis() - tiempo > 1500)) {
    frenando = true;
  }

  if (frenando && !acelerando) {
    static unsigned long ultimoFreno = 0;
    if (millis() - ultimoFreno > 100) {
      ultimoFreno = millis();
      if (velocidad > 0) {
        velocidad -= 20;
        if (velocidad < 0) velocidad = 0;
        analogWrite(ENA, velocidad);
        analogWrite(ENB, velocidad);
      }
      else {
        frenando = false;
        digitalWrite(LED_B, LOW);
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
      }
    }
  }

  Serial.println(velocidad);
}

void sonar_bocina() {
  tone(BUZZ, 1200, 200);
  delay(300);
  noTone(BUZZ);
}

void aumentarMarcha() {
  Serial.println(velocidad);
  if (velocidad + 50 < velocidadMax) velocidad += 50;
  else velocidad = velocidadMax;
}

void reducirMarcha() {
  velocidad -= 50;
  if (velocidad <= 0) velocidad = 0;
}
