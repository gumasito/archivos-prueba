#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Sobrero Wifi";
const char* password = "mis03hijos";
WebServer server(80);
const int led = 23;

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("IP del ESP32: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());

  server.on("/led/on", []() {
    digitalWrite(led, HIGH);
    Serial.println("Luz Prendida");
    server.send(200, "text/plain", "LED encendido");
  });

  server.on("/led/off", []() {
    digitalWrite(led, LOW);
    Serial.println("Luz Apagada");
    server.send(200, "text/plain", "LED apagado");
  });

  server.begin();
  Serial.println("Servidor web listo!");
}

void loop() {
  server.handleClient();
}
