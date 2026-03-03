#include "BluetoothSerial.h"   // Librería Bluetooth

BluetoothSerial SerialBT;      // Crea el objeto Bluetooth
const int relePin = 5;         // Pin donde está conectado el relé
char dato;                     // Variable para guardar los datos recibidos

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT_Rele");  // Nombre del dispositivo Bluetooth
  pinMode(relePin, OUTPUT);
  digitalWrite(relePin, LOW);       // Relé apagado al inicio
  
  Serial.println("ESP32 listo. Empareja el dispositivo Bluetooth y envía comandos.");
}

void loop() {
  // Si se recibe un dato por Bluetooth
  if (SerialBT.available()) {
    dato = SerialBT.read();  // Lee un carácter

    // Mostrar en el monitor serie
    Serial.print("Dato recibido: ");
    Serial.println(dato);

    // Encender o apagar el relé según el comando
    if (dato == '1') {
      digitalWrite(relePin, HIGH);
      SerialBT.println("Rele encendido");
      Serial.println("Rele encendido");
    }
    else if (dato == '0') {
      digitalWrite(relePin, LOW);
      SerialBT.println("Rele apagado");
      Serial.println("Rele apagado");
    }
  }

  delay(20);  // Pequeño retardo para estabilidad
}
