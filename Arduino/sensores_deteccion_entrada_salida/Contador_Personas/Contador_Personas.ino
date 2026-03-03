#define sensor1 = ¡¡;
#define sensor2 = !!;

bool primer_sensor = false;
bool segundo_sensor = false;

bool back_primer = false;
bool back_segundo = false;

int alumno = 0;
int alumnos = 0;
int profes = 0;
static unsigned long checkeo = 0;
static unsigned long checkeo_dos = 0;
void setup() {
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
}

void loop() {
  primer_sensor = digitalRead(sensor1);
  segundo_sensor = digitalRead(sensor2);
  if (primero && !segundo) {
    entro ++;
  } else if (primero && segundo) {
    transitando = true;
  } else if (!primero && segundo) {
    salio ++;
  } else {
    if (millis() - ultima_pp > 36000) {
      transitando = false;
      entro = 0;
      salio = 0;
    }
    transitando = false;
    Serial.println("Entraron " + entro);
    Serial.println("Salieron " + salio);
    if (entro > salio) {
      Serial.print("Entraron y quedaron en medio");
    } else if (entro < salio) {
      Serial.println("Salieron y quedaron en mitad");
    } else {
      Serial.println("Se fueron todos");
    }
  }
  if (millis() - checkeo > 100) {
    if (primer_sensor && !back_primer) {
      alumno++;
      alumnos = alumno;
      primero = true;
    }
    back_primer = primer_sensor;
    checkeo = millis();
  }
  if (segundo_sensor && millis() - checkeo_dos > 100) {
    if (segundo_sensor && !back_segundo) {
      alumno --;
      if (alumno < 0) alumno = 0;
    }
    back_segundo = segundo_sensor;
    checkeo_dos = millis();
  }
  if (!primer_sensor && !segundo_sensor) {
    if (alumno > 0) {
      profes = alumno;
      Serial.println("Ingresaron a la escuela un total de " + alumnos);
      Serial.println("Ingresaron un total de " + profes + "a la direccion");
      alumnos = 0;
    }
  }
}
