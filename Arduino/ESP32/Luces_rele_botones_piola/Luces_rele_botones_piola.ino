#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Sobrero Wifi";
const char* password = "mis03hijos";
  
WebServer server(80);

// Pines
const int led1 = 22;
const int led2 = 23;

// Estados
bool estadoLed1 = false;
bool estadoLed2 = false;

// 👉 Estado general: si ambos están encendidos
bool obtenerEstadoGeneral() {
  return estadoLed1 && estadoLed2;
}

// Cambia los dos LEDs a la vez
void manejarTodo() {
  bool nuevoEstado = !obtenerEstadoGeneral();
  estadoLed1 = nuevoEstado;
  estadoLed2 = nuevoEstado;

  digitalWrite(led1, estadoLed1);
  digitalWrite(led2, estadoLed2);

  server.send(200, "text/plain", nuevoEstado ? "Aro encendido ✅" : "Aro apagado ❌");
}

// Cambia LED 1
void manejarLed1() {
  estadoLed1 = !estadoLed1;
  digitalWrite(led1, estadoLed1);
  server.send(200, "text/plain", estadoLed1 ? "Led 1 encendido ✅" : "Led 1 apagado ❌");
}

// Cambia LED 2
void manejarLed2() {
  estadoLed2 = !estadoLed2;
  digitalWrite(led2, estadoLed2);
  server.send(200, "text/plain", estadoLed2 ? "Led 2 encendido ✅" : "Led 2 apagado ❌");
}
void manejarRoot() {
  String html = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <title>Aro de Luz</title>
    <meta charset="UTF-8">
    <style>
      body { text-align: center; font-family: Arial; margin-top: 40px; }
      button { font-size: 18px; padding: 10px 20px; margin: 10px; }
    </style>
  </head>
  <body>
    <h2>Aro de Luz</h2>

    <p><b>Estado general:</b> <span id="estadoGeneral">Desconocido</span></p>
    <button onclick="controlarTodo()">Encender/Apagar Todo</button><br>

    <p><b>Led 1:</b> <span id="estadoLed1">Desconocido</span></p>
    <button onclick="controlarLed1()">Encender/Apagar Led 1</button><br>

    <p><b>Led 2:</b> <span id="estadoLed2">Desconocido</span></p>
    <button onclick="controlarLed2()">Encender/Apagar Led 2</button><br>

    <script>
      function controlarTodo() {
        fetch("/todo")
          .then(res => res.text())
          .then(texto => {
            document.getElementById("estadoGeneral").innerText = texto;
              actualizarTodosLosEstados();
          });
      }

      function controlarLed1() {
        fetch("/led1")
          .then(res => res.text())
          .then(texto => {
            document.getElementById("estadoLed1").innerText = texto;
            actualizarTodosLosEstados();
          });
      }

      function controlarLed2() {
        fetch("/led2")
          .then(res => res.text())
          .then(texto => {
            document.getElementById("estadoLed2").innerText = texto;
            actualizarTodosLosEstados();
          });l
      }

      function actualizarTodosLosEstados() {
        fetch("/estado")
          .then(res => res.json())
          .then(data => {
            document.getElementById("estadoGeneral").innerText = data.general;
            document.getElementById("estadoLed1").innerText = data.led1;
            document.getElementById("estadoLed2").innerText = data.led2;
          });
      }

      // Actualiza al cargar la página
      actualizarTodosLosEstados();
    </script>
  </body>
  </html>
  )rawliteral";

  server.send(200, "text/html", html);
}
void manejarEstado() {
  String json = "{";
  json += "\"general\":\"" + String(obtenerEstadoGeneral() ? "Aro encendido ✅" : "Aro apagado ❌") + "\",";
  json += "\"led1\":\"" + String(estadoLed1 ? "Led 1 encendido ✅" : "Led 1 apagado ❌") + "\",";
  json += "\"led2\":\"" + String(estadoLed2 ? "Led 2 encendido ✅" : "Led 2 apagado ❌") + "\"";
  json += "}";
  server.send(200, "application/json", json);
}
void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado:");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());

  // Rutas
  server.on("/", manejarRoot);
  server.on("/todo", manejarTodo);
  server.on("/led1", manejarLed1);
  server.on("/led2", manejarLed2);
  server.on("/estado", manejarEstado);

  server.begin();
  Serial.println("Servidor listo.");
}
void loop() {
  server.handleClient();  // Atiende peticiones del navegador
}
