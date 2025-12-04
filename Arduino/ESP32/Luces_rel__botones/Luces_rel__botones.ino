#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoOTA.h>

const char* ssid = "Sobrero Wifi";
const char* password = "mis03hijos";

WebServer server(80);

const int pinPower2 = 23; // Cable blanco
const int pinPower = 22; // Relé que controla el 5V del aro

bool encendido = false;
bool encendidoUno = false;
bool encendidoDos = false;


void handleRoot() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head><title>Aro de Luz</title></head>
    <meta charset="UTF-8">
    <body style="text-align:center;">
      <h2>Aro de Luz</h2>
      <button onclick="fetch('/todo')">Encender/Apagar Todo</button><br><br>)rawliteral";
  // Estado general
  html += "<p><b>Aro: ";
  html += (encendido ? "Encendido ✅" : "Apagado ❌");
  html += "</b></p>";

  // Estado Led 1
  html += "<p><b>Led 1: ";
  html += (encendidoUno ? "Encendido ✅" : "Apagado ❌");
  html += "</b></p>";

  // Estado Led 2
  html += "<p><b>Led 2: ";
  html += (encendidoDos ? "Encendido ✅" : "Apagado ❌");
  html += "</b></p>";

  // Botones
  html += R"rawliteral(
      <button onclick="fetch('/uno')">Encender/Apagar Led 1</button><br><br>
      <button onclick="fetch('/dos')">Encender/Apagar Led 2</button><br><br>
      <button onclick="fetch('/cambiar')">Cambiar Color</button>
    </body>
    </html>
  )rawliteral";
  server.send(200, "text/html", html);
}

void handleTogglePower() {
  encendido = !encendido;
  digitalWrite(pinPower, encendido ? HIGH : LOW);
  digitalWrite(pinPower2, encendido ? HIGH : LOW);
  server.send(200, "text/plain", encendido ? "Encendido" : "Apagado");
}
void prenderUno() {
  encendidoUno = !encendidoUno;
  digitalWrite(pinPower, encendidoUno ? HIGH : LOW);
  if (encendidoUno) {
    server.send(200, "text/plain", "Led Uno encendido");
  }
  else {
    server.send(200, "text/plain", "Led Uno apagado");
  }
}
void prenderDos() {
  encendidoDos = !encendidoDos;
  digitalWrite(pinPower2, encendidoDos ? HIGH : LOW);
  if (encendidoDos) {
    server.send(200, "text/plain", "Led Dos encendido");
  }
  else {
    server.send(200, "text/plain", "Led Dos Apagado");
  }
}
void handleCambioColor() {
  if (encendido) {
    //simularPulsacion();
    server.send(200, "text/plain", "Color cambiado");
  } else {
    server.send(200, "text/plain", "Primero encendé el aro");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(pinPower2, OUTPUT);
  digitalWrite(pinPower2, LOW);

  pinMode(pinPower, OUTPUT);
  digitalWrite(pinPower, LOW); // Apagado al inicio

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado: ");
  Serial.println(WiFi.localIP());
  ArduinoOTA.setHostname("esp32-aro");

  // Mensajes opcionales (debug)
  ArduinoOTA.onStart([]() {
    Serial.println("Inicio de OTA");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nOTA finalizada");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progreso: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Fallo de autenticación");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Error al comenzar");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Error de conexión");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Error al recibir");
    else if (error == OTA_END_ERROR) Serial.println("Error al finalizar");
  });

  ArduinoOTA.begin();
  Serial.println("OTA lista");

  server.on("/", handleRoot);
  server.on("/uno", prenderUno);
  server.on("/dos", prenderDos);
  server.on("/todo", handleTogglePower);
  //server.on("/cambiar", handleCambioColor);
  server.begin();
}

void loop() {
  ArduinoOTA.handle();
  server.handleClient();
}
