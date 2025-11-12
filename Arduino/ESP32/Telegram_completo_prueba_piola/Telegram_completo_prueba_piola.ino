#include <WiFi.h>
#include <WebServer.h>
#include <UniversalTelegramBot.h>


#define MAX_USERS 10

const char* token = "7579691226:AAEq-6KBvV-_2bwQVhWmM-yC7NLBr0NxaME";
String chat_ids[] = {
  "7848546381",
  "5830886971"
};
int current_users = 2;
#include <WiFiClientSecure.h>

const char* ssid = "Sobrero Wifi";
const char* password = "mis03hijos";
unsigned long lastCheck = 0;

WebServer server(80);
WiFiClientSecure client;
UniversalTelegramBot bot(token, client);

//pines
const int led1 = 22;
const int led2 = 23;

//estados
bool estadoLed1 = false;
bool estadoLed2 = false;

void SendMessageToAll(String message) {
  for (int i = 0; i < current_users; i++) {
    bot.sendMessage(chat_ids[i], message, "");
  }
}
bool usuariosAutorizados(String id) {
  for (int i = 0; i < current_users ; i++) {
    if (chat_ids[i] == id) return true;
  } return false;
}
bool agregarUsuario(String nuevoID) {
  if (current_users >= MAX_USERS) return false;
  for (int i = 0; i < current_users; i++) {
    if (chat_ids[i] == nuevoID) return false;
  }
  chat_ids[current_users++] = nuevoID;
  //chat_ids[numUsers] = nuevoID;
  //numUsers++;
  //es lo mismo
  return true;
}
bool estadoGeneral() {
  return estadoLed1 && estadoLed2;
}
void ManejarTodo() {
  bool nuevoValor = !estadoGeneral();

  estadoLed1 = nuevoValor;
  estadoLed2 = nuevoValor;

  digitalWrite(led1, estadoLed1);
  digitalWrite(led2, estadoLed2);

  server.send(200, "text/plain", nuevoValor ? "Estan todas encendidas" : "Estan todas apagadas");
}
void ManejarLed1() {
  estadoLed1 = !estadoLed1;
  digitalWrite(led1, estadoLed1);
  server.send(200, "text/plain", estadoLed1 ? "Led 1 Encendido" : "Led 1 Apagado");

}
void ManejarLed2() {
  estadoLed2 = !estadoLed2;
  digitalWrite(led2, estadoLed2);
  server.send(200, "text/plain", estadoLed2 ? "Led 2 Encendido" : "Led 2 Apagado");
}
void ManejarEstado() {
  String json = "{";
  json += "\"general\":\"" + String(estadoGeneral() ? "Estan todas encendidas" : "Estan todas apagadas") + "\",";
  json += "\"led1\":\"" + String(estadoLed1 ? "Led 1 encendido" : "Led 1 apagado") + "\",";
  json += "\"led2\":\"" + String(estadoLed2 ? "Led 2 encendido" : "Led 2 apagado") + "\"";
  json += "}";
  server.send(200, "application/json", json);
}
void ManejarRoot() {
  String html = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
  <meta charset="UTF-8">
  <title>Prueba 2</title>
  </head>
  <body>
  <h2>Luces de la casa</h2>
  <p><b>Todo: </b> <span id="estadoGeneral">Desconocido</span></p>
  <button onclick="CambiarTodo()">Encender/Apagar Todo</button><br>

  <p><b>Led 1: </b> <span id="estadoLed1">Desconocido</span></p>
  <button onclick="CambiarLed1()">Encender/Apagar Led1</button><br>

  <p><b>Led 2: </b> <span id="estadoLed2">Desconocido</span></p>
  <button onclick="CambiarLed2()">Encender/Apagar Led2</button><br>

  <script>
  function CambiarTodo(){
    fetch("/todo")
      .then(res => res.text())
      .then(texto => {
        document.getElementById("estadoGeneral").innerText = texto;
        ActualizarEstados();
      });
      }
  function CambiarLed1(){
    fetch("/uno")
      .then(res => res.text())
      .then(texto => {
        document.getElementById("estadoLed1").innerText = texto;
        ActualizarEstados();
      });
  }
  function CambiarLed2(){
    fetch("/dos")
      .then(res => res.text())
      .then(texto => {
        document.getElementById("estadoLed2").innerText = texto;
        ActualizarEstados();
      });
  }
  function ActualizarEstados(){
    fetch("/estado")
      .then(res => res.json())
      .then(data =>{
        document.getElementById("estadoGeneral").innerText = data.general;
        document.getElementById("estadoLed1").innerText = data.led1;
        document.getElementById("estadoLed2").innerText = data.led2;
      });
  }
  ActualizarEstados();
  </script>
  </body>
  </html>)rawliteral";
  server.send(200, "text/html", html);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);

  client.setInsecure();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Conexion Exitosa");
  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.localIP());

  SendMessageToAll("Conexion Exitosa\n");

  server.on("/", ManejarRoot);
  server.on("/todo", ManejarTodo);
  server.on("/uno", ManejarLed1);
  server.on("/dos", ManejarLed2);
  server.on("/estado", ManejarEstado);
  server.begin();
  Serial.println("Servidor Listo");
  bot.sendMessage(chat_ids[0], "Servidor Listo :), Felicidades", "");
}

void loop() {
  if (millis() - lastCheck > 1000) {
    int new_msg = bot.getUpdates(bot_last_message_received + 1);
    while (new_msg) {
      for (int i = 0; i < new_msg; i++) {
        String msg = bot.messages[i].text;
        String sender_id = bot.messages[i].chat_id;
        Serial.print("Mensaje recibido: ");
        Serial.print(msg);
        Serial.print(" de ");
        Serial.println(sender_id);
        if (usuariosAutorizados(sender_id)) {
          if (msg == "/help") {
            bot.sendMessage(sender_id, "Lista de comandos, blah blah blah :)", "");
          } else if (msg == "/led1") {
            if (estadoLed1) {
              bot.sendMessage(sender_id, "Esta luz ya está prendida", "");
              ManejarLed1();  // cambia el estado
              bot.sendMessage(sender_id, "Ahora está apagada", "");
            } else {
              bot.sendMessage(sender_id, "Esta luz está apagada", "");
              ManejarLed1();
              bot.sendMessage(sender_id, "Ahora está prendida", "");
            }
          } else if (msg == "/led2") {
            if (estadoLed2) {
              bot.sendMessage(sender_id, "Esta luz ya está prendida", "");
              ManejarLed2();
              bot.sendMessage(sender_id, "Ahora está apagada", "");
            } else {
              bot.sendMessage(sender_id, "Esta luz está apagada", "");
              ManejarLed2();
              bot.sendMessage(sender_id, "Ahora está prendida", "");
            }
          }
          else if (msg == "/todo") {
            if (estadoGeneral()) {
              bot.sendMessage(sender_id, "Está todo prendido", "");
              ManejarTodo();
              bot.sendMessage(sender_id, "Ahora está todo apagado", "");
            } else {
              bot.sendMessage(sender_id, "Está todo apagado", "");
              ManejarTodo();
              bot.sendMessage(sender_id, "Ahora está todo prendido", "");
            }
          } else if (msg.startsWith("/add") && sender_id == chat_ids[0]) {
            int espacio = msg.indexOf(" ");
            if (espacio != -1) {
              String nuevoID = msg.substring(espacio + 1);
              if (agregarUsuario(nuevoID)) {
                bot.sendMessage(sender_id, "Usuario " + nuevoID + " fue agregado exitosamente", "");
              } else {
                bot.sendMessage(sender_id, "Ya se ha alcanzado el limite de usuarios o hubo algun error", "");
              }
            } else {
              bot.sendMessage(sender_id, "Intenta escribir '/add <chat_id>'", "");
            }
          } else {
            bot.sendMessage(sender_id, "Intenta escribiendo '/help'", "");
          }
        } else {
          for (int i = 0; i < current_users; i++) {
            bot.sendMessage(chat_ids[0], "Se ha intentado unir un intruso", "");
          }
        }
      }
      new_msg = bot.getUpdates(bot.last_message_received + 1);
    }
    lastCheck = millis();
  }
  server.handleClient();
}
