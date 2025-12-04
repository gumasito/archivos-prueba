int pin1 = 5; // Azul
int pin2 = 6; // Verde
int pin3 = 9; // Rojo

int quest;
int quest1;
int quest2;

void setup() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  Serial.begin(9600);
  Serial.println("Listo para recibir valores de color RGB (0 a 255).");
}

void loop() {
  // Color Rojo
  Serial.println("Elija un valor para el color Rojo (0-255): ");
  while (Serial.available() == 0) {
    // Esperando entrada
  }
  quest = Serial.parseInt();
  analogWrite(pin3, quest);
  delay(100);

  // Limpiar buffer
  while (Serial.available() > 0) Serial.read();

  // Color Verde
  Serial.println("Elija un valor para el color Verde (0-255): ");
  while (Serial.available() == 0) {
    // Esperando entrada
  }
  quest1 = Serial.parseInt();
  analogWrite(pin2, quest1);
  delay(100);
  while (Serial.available() > 0) Serial.read();

  // Color Azul
  Serial.println("Elija un valor para el color Azul (0-255): ");
  while (Serial.available() == 0) {
    // Esperando entrada
  }
  quest2 = Serial.parseInt();
  analogWrite(pin1, quest2);
  delay(100);
  while (Serial.available() > 0) Serial.read();

  Serial.println("Color actualizado.\n");
}
