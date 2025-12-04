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
  long distancia1 = medirDistancias(pinTrig1, pinEco1);
  long distancia2 = medirDistancias(pinTrig2, pinEco2);

  if (distancia1 < umbral) {
    t1 = millis();
    while (millis() - t1 < tiempo_espera) {
      distancia2 = medirDistancias(pinTrig2, pinEco2);
      if (distancia2 < umbral) {
        Serial.println(">>Ingreso un alumno");
        digitalWrite(led1, HIGH);
        delay(1000);
        digitalWrite(led1, LOW);
        continue;
      }else if( distancia2 > umbral){
        Serial.println(">>Ingreso un profesor");
      }
    }
  } else if (distancia2 < umbral) {
    t2 = millis();
    while (millis() - t2 < tiempo_espera) {
      distancia1 = medirDistancias(pinTrig1, pinEco1);
      if (distancia1 < umbral) {
        Serial.println("<<Salio un alumno");
        digitalWrite(led2, HIGH);
        delay(1000);
        digitalWrite(led2, LOW);
        continue;
      }else if (distancia > umbral){
        Serial.println("<<Salio un profesor");
      }
    }
  }
  delay(200);
}
