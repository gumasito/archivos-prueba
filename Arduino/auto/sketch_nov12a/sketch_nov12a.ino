#define IN1 9//32
#define IN2 8//33 //8
#define ENA 6//35 // 6

#define LED 12 //12
#define LED_B 13 //13

#define IN3 3//26 //3
#define IN4 2//27 //2
#define ENB 5//14 //5

void setup() {
  // Configurar pines de salida
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  Serial.begin(9600);
  Serial.println("Control de motores listo");
}

void loop() {
  // Mover hacia adelante
  adelante();
  delay(2000);

  // Detener
  detener();
  delay(1000);

  // Mover hacia atrás
  atras();
  delay(2000);

  // Detener
  detener();
  delay(2000);
}

// -------- FUNCIONES --------

void adelante() {
  Serial.println("Adelante");

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 255);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 255);
}

void atras() {
  Serial.println("Atras");

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 255);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 255);
}

void detener() {
  Serial.println("Detener");

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}
