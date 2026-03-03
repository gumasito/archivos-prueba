const int pinEco1 = 9;
const int pinEco2 = 13;
const int pinTrig1 = 10;
const int pinTrig2 = 11;

int led1 = 2;
int led2 = 3;

unsigned long tiempo_espera = 2000;
unsigned long t1, t2;

int umbral = 600;
void setup () {
  Serial.begin(9600);
  pinMode(pinEco1, INPUT);
  pinMode(pinEco2, INPUT);
  pinMode(pinTrig1, OUTPUT);
  pinMode(pinTrig2, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}
long medirDistancias(int trig, int eco) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  return pulseIn(eco, HIGH);
}
void loop() {
  int distancia1 = medirDistancias(pinTrig1, pinEco1);
  int distancia2 = medirDistancias(pinTrig2, pinEco2);

  if (distancia2 < umbral) {
    t1 = millis();
    bool detectado = false;

    while (millis() - t1 < tiempo_espera) {
      if (!detectado) {
        int d1 = medirDistancias(pinTrig1, pinEco1);

        if (d1 < umbral) {
          Serial.println(">>>Ha entrado un alumno");
          detectado = true;
        } else {
          Serial.println(">>>Ha entrado un profesor");
          detectado = true;
        }
      }
    }
  }

  else if (distancia1 < umbral) {
    t2 = millis();
    bool detectado = false;

    while (millis() - t2 < tiempo_espera) {
      if (!detectado) {
        int d2 = medirDistancias(pinTrig2, pinEco2);

        if (d2 < umbral) {
          Serial.println("<<<Ha salido un alumno");
          detectado = true;
        } else {
          Serial.println("<<<Ha salido un profesor");
          detectado = true;
        }
      }
    }
  }
}
