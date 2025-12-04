#include <WiFi.h>
#include <WebServer.h>
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>

const char* token = "7579691226:AAEq-6KBvV-_2bwQVhWmM-yC7NLBr0NxaME";
#define MAX_USERS 10
String chat_ids[MAX_USERS] = {
  "7848546381",  // admin
  "5830886971"
};
int numUsers = 2; // cantidad inicial de usuarios

unsigned long lastCheck = 0;

const char* ssid = "Sobrero Wifi";
const char* password = "mis03hijos";

WebServer server(80);
WiFiClientSecure client;
UniversalTelegramBot bot(token, client);

// Pines
const int led1 = 22;
const int led2 = 23;

// Estados
bool estadoLed1 = false;
bool estadoLed2 = false;
//Mensaje a todos
void sendMessageToAll(String mensaje) {
  for (int i = 0; i < numUsers; i++) {
    bot.sendMessage(chat_ids[i], mensaje, "");
  }
}
// Verificar si esta permitido o no
bool esUsuarioPermitido(String id) {
  for (int i = 0; i < numUsers; i++) {
    if (chat_ids[i] == id) return true;
  }   
  return false;
}
// 👉 Estado general: si ambos están encendidos
bool obtenerEstadoGeneral() {
  return estadoLed1 && estadoLed2;
}
bool agregarUsuario(String nuevoID) {
  if (numUsers >= MAX_USERS) return false;
  for (int i = 0; i < numUsers; i++) {
    if (chat_ids[i] == nuevoID) return false; // Ya existe
  }
  chat_ids[numUsers++] = nuevoID;
  //chat_ids[numUsers] = nuevoID;
  //numUsers++;
  //es lo mismo
  return true;
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
          });
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
  client.setInsecure();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  sendMessageToAll("Conexion Exitosa");
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
  if (millis() - lastCheck > 1000) {  // chequea cada 1 segundo
    int newMsg = bot.getUpdates(bot.last_message_received + 1);

    while (newMsg) {
      for (int i = 0; i < newMsg; i++) {
        String msg = bot.messages[i].text;
        String senderID = bot.messages[i].chat_id;
        Serial.print("Mensaje Recibido: " + msg +" de " + senderID);
        if (esUsuarioPermitido(senderID)) {
          if (msg == "/help") {
            bot.sendMessage(senderID, "Lista de comandos:\n/led1 - /led2 - /todo", "");
          }
          else if (msg == "/led1") {
            if (estadoLed1) {
              bot.sendMessage(senderID, "Esta luz ya está prendida", "");
              manejarLed1();  // cambia el estado
              bot.sendMessage(senderID, "Ahora está apagada", "");
            } else {
              bot.sendMessage(senderID, "Esta luz está apagada", "");
              manejarLed1();
              bot.sendMessage(senderID, "Ahora está prendida", "");
            }
          }
          else if (msg == "/led2") {
            if (estadoLed2) {
              bot.sendMessage(senderID, "Esta luz ya está prendida", "");
              manejarLed2();
              bot.sendMessage(senderID, "Ahora está apagada", "");
            } else {
              bot.sendMessage(senderID, "Esta luz está apagada", "");
              manejarLed2();
              bot.sendMessage(senderID, "Ahora está prendida", "");
            }
          }
          else if (msg == "/todo") {
            if (obtenerEstadoGeneral()) {
              bot.sendMessage(senderID, "Está todo prendido", "");
              manejarTodo();
              bot.sendMessage(senderID, "Ahora está todo apagado", "");
            } else {
              bot.sendMessage(senderID, "Está todo apagado", "");
              manejarTodo();
              bot.sendMessage(senderID, "Ahora está todo prendido", "");
            }
          } else if (msg.startsWith("/add") && senderID == chat_ids[0]) {
            int espacio = msg.indexOf(" ");
            if (espacio != -1) {
              String nuevoID = msg.substring(espacio + 1);
              if (agregarUsuario(nuevoID)) {
                bot.sendMessage(senderID, "Usuario: " + nuevoID + " Agregado Exitosamente", "");
              } else {
                bot.sendMessage(senderID, "No se pudo agregar!!", "");
              }
            }
            else {
              bot.sendMessage(senderID, "Usa el formato correcto '/add <id>'", "");
            }
          }
          else {
            bot.sendMessage(senderID, "Por más ayuda, escribe '/help'", "");
          }
        } else {
          for (int i = 0; i < numUsers; i++) {
            bot.sendMessage(chat_ids[i], "Alguien no autorizado intentó enviar comandos.");
          }
        }
      }
      newMsg = bot.getUpdates(bot.last_message_received + 1);
    }
    lastCheck = millis();
  }
  server.handleClient();  // Atiende peticiones del navegador
}
