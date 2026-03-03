#include <WiFi.h>
#include <WebServer.h>
#include <UniversalTelegramBot.h>
#include "SPIFFS.h"
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "esp_task_wdt.h"


#define WDT_TIMEOUT 10
#define MAX_USERS 10

String telegramToken;
String chat_ids[MAX_USERS];
String ssid1, pass1, ssid2, pass2;

int current_users = 0;

unsigned long lastCheck = 0;

WebServer server(80);
WiFiClientSecure client;
UniversalTelegramBot* bot; //puntero que busca la variable "bot" con los valores a utilizar

//pines
const int led1 = 22;
const int led2 = 23;

const int sensor_pir_puerta = **;
const int luz_pir_puerta = **;

//estados
bool estadoLed1 = false;
bool estadoLed2 = false;

bool estadoPirPuerta = false; //Valor actual de lectura
bool PIRCheck = false; //Valor anterior de lectura
static unsigned long lastPIR = 0; //evitar debounce

void ensureWiFi() {
  static unsigned long lastAttempt = 0;
  if (WiFi.status() != WL_CONNECTED && millis() - lastAttempt > 5000) {
    lastAttempt = millis();
    WiFi.reconnect();
  }
}
bool loadConfig() {
  File conf = SPIFFS.open("/config.json", "r");
  if (!conf) {
    Serial.println("Error al abrir config.json");
    return false;
  }
  StaticJsonDocument<1024> docConf;
  DeserializationError error = deserializeJson(docConf, conf);
  conf.close();
  if (error) {
    Serial.println("Error parseando JSON");
    return false;
  }
  telegramToken = docConf["telegram"]["token"].as<String>();
  JsonArray ids = docConf["telegram"]["chat_ids"];
  current_users = 0;
  for (String id : ids) {
    chat_ids[current_users++] = id;
  }
  ssid1 = docConf["wifi"]["ssid"].as<String>();
  pass1 = docConf["wifi"]["pass"].as<String>();
  ssid2 = docConf["wifi"]["ssid2"].as<String>();
  pass2 = docConf["wifi"]["pass2"].as<String>();
  return true;
}
void saveConfig() {
  StaticJsonDocument<1024> doc;

  JsonArray ids = doc.createNestedObject("telegram").createNestedArray("chat_ids");
  for (int i = 0; i < current_users; i++) {
    ids.add(chat_ids[i]);
  }

  doc["telegram"]["token"] = telegramToken;

  doc["wifi"]["ssid"] = ssid1;
  doc["wifi"]["pass"] = pass1;
  doc["wifi"]["ssid2"] = ssid2;
  doc["wifi"]["pass2"] = pass2;

  File file = SPIFFS.open("/config.json", "w");
  serializeJson(doc, file);
  file.close();
}

void SendMessageToAll(String message) {
  for (int i = 0; i < current_users; i++) {
    bot.sendMessage(chat_ids[i], message, "");
  }
}

bool estadoPuerta(int sensor) {
  estadoPirPuerta = digitalRead(sensor);
  if (estadoPirPuerta && !PIRCheck) {
    digitalWrite(luz_pir_puerta, HIGH);
  }
  PIRCheck = estadoPirPuerta;
  return estadoPirPuerta;
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
  return estadoLed1 && estadoLed2; // F & F = F - V & V = V - F & V = F
}
void ManejarTodo() {
  bool nuevoValor = !estadoGeneral(); // F = V - V = F

  estadoLed1 = nuevoValor;
  estadoLed2 = nuevoValor;

  digitalWrite(led1, estadoLed1);
  digitalWrite(led2, estadoLed2);

  server.send(200, "text/plain", nuevoValor ? "Estan todas encendidas" : "Estan todas apagadas");
}
void ManejarLed(int num) {
  if (num == 1) {
    estadoLed1 = !estadoLed1;
    digitalWrite(led1, estadoLed1);
    server.send(200, "text/plain", estadoLed1 ? "Led 1 encendida" : "Led 1 apagada");
  }
  else if (num == 2) {
    estadoLed2 = !estadoLed2;
    digitalWrite(led2, estadoLed2);
    server.send(200, "text/plain", estadoLed2 ? "Led 2 encendida" : "Led 2 apagada");
  }
}
void ManejarEstado() {
  StaticJsonDocument<200> doc;
  doc["general"] = estadoGeneral() ? "Estan todas encendidas" : "Estan todas apagadas";
  doc["led1"] = estadoLed1 ? "Led 1 encendido" : "Led 1 apagado";
  doc["led2"] = estadoLed2 ? "Led 2 encendido" : "Led 2 apagado";
  doc["Sensor_PIR"] = estadoPirPuerta ? "Hay Alguien" : "No Hay Nadie";
  String output;
  serializeJson(doc, output);
  server.send(200, "application/json", output);
}
void ManejarRoot() {
  File file = SPIFFS.open("/index.html", "r");
  if (!file) {
    server.send(404, "text/plain", "No se encontró el archivo index.html");
    return;
  }
  server.streamFile(file, "text/html");
  file.close();
}
String Users(String user) {
  if (chat_ids[0] && current_users > 0 == user) {
    return "admin";
  } else if (chat_ids[1] && current_users > 1 == user) {
    return "user1";
  }
  return "desconocido";
}
void setup() {
  Serial.begin(115200);
  client.setInsecure();
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  pinMode(sensor_pir_puerta, INPUT);
  pinMode(luz_pir_puerta, OUTPUT);
  digitalWrite(luz_pir_puerta, LOW);
  esp_task_wdt_init(WDT_TIMEOUT,true);
  esp_task_wdt_add(NULL);
  if (!SPIFFS.begin(true)) {
    Serial.println("Error montando SPIFFS");
  }
  loadConfig(); //funcion para manejar datos de los spiffs de las variables de telegram y conexion a la red
  if (telegramToken.length() > 0) {
    bot = new UniversalTelegramBot(telegramToken, client);
  }
  WiFi.begin(ssid1.c_str(), pass1.c_str());
  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startTime < 30000) {  // Wait up to 30s
    delay(300);
    Serial.print(".");
  }
  if (WiFi.status() != WL_CONNECTED) {
    // Fallback to secondary WiFi
    Serial.println("\nFallo en WiFi primario, intentando secundario...");
    WiFi.begin(ssid2.c_str(), pass2.c_str());
    startTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startTime < 30000) {
      delay(500);
      Serial.print(".");
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConexion Exitosa");
    Serial.println(WiFi.localIP());  // Print IP for web access
    SendMessageToAll("Conexion Exitosa\nIP: " + WiFi.localIP().toString());
  } else {
    Serial.println("\nError: No se pudo conectar a WiFi. Reiniciando...");
    ESP.restart();  // Restart if no connection
  }

  Serial.println("Conexion Exitosa");

  Serial.println(WiFi.macAddress());


  SendMessageToAll("Conexion Exitosa\n");

  server.on("/", ManejarRoot);
  server.on("/todo", ManejarTodo);
  server.on("/uno", []() {
    ManejarLed(1);
  });
  server.on("/dos", []() {
    ManejarLed(2);
  });
  server.on("/estado", ManejarEstado);
  server.begin();
  Serial.println("Servidor Listo");
  bot.sendMessage(chat_ids[0], "Servidor Listo :), Felicidades", "");
}

void loop() {
  esp_task_wdt_reset();
  if (millis() - lastPIR > 500) {
    estadoPuerta(sensor_pir_puerta);
    lastPIR = millis();
  }
  String script = "/led1: cocina - /led2: pasillo - /todo: todo - /estado: Estado de luces - /sensor: Puerta Casa";
  ensureWiFi();
  if (millis() - lastCheck > 1000) {
    int new_msg = bot.getUpdates(bot.last_message_received + 1);
    while (new_msg) {
      for (int i = 0; i < new_msg; i++) {
        String msg = bot.messages[i].text;
        String sender_id = bot.messages[i].chat_id;
        Serial.print("Mensaje recibido: ");
        Serial.print(msg);
        Serial.print(" de ");
        Serial.println(Users(sender_id));
        String mensaje = "";
        mensaje +=  estadoLed1 ? "Luz 1 Encendida" : "Luz 1 Apagada";
        mensaje += "\n";
        mensaje +=  estadoLed2 ? "Luz 2 Encendida" : "Luz 2 Apagada";
        mensaje += "\n";
        mensaje += estadoPirPuerta ? "Hay Alguien" : "No Hay Nadie";
        if (usuariosAutorizados(sender_id)) {
          if (msg == "/help") {
            bot.sendMessage(sender_id, script, "");
          } else if (msg == "/led1") {
            if (estadoLed1) {
              bot.sendMessage(sender_id, "Esta luz ya está prendida", "");
              ManejarLed(1);  // cambia el estado
              bot.sendMessage(sender_id, "Ahora está apagada", "");
            } else {
              bot.sendMessage(sender_id, "Esta luz está apagada", "");
              ManejarLed(1);
              bot.sendMessage(sender_id, "Ahora está prendida", "");
            }
          } else if (msg == "/led2") {
            if (estadoLed2) {
              bot.sendMessage(sender_id, "Esta luz ya está prendida", "");
              ManejarLed(2);
              bot.sendMessage(sender_id, "Ahora está apagada", "");
            } else {
              bot.sendMessage(sender_id, "Esta luz está apagada", "");
              ManejarLed(2);
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
          } else if (msg == "/estado") {
            bot.sendMessage(sender_id, mensaje, "");
          } else if (msg == "/sensor") {
            if (estadoPuerta(sensor_pir_puerta)) {
              bot.sendMessage(sender_id, "Hay Alguien", "");
            } else {
              bot.sendMessage(sender_id, "No Hay Nadie", "");
            }
          } else if (msg.startsWith("/add") && sender_id == chat_ids[0]) {
            int espacio = msg.indexOf(" ");
            if (espacio != -1) {
              String nuevoID = msg.substring(espacio + 1);
              if (agregarUsuario(nuevoID)) {
                saveConfig();
                bot.sendMessage(sender_id, "Usuario " + nuevoID + " fue agregado exitosamente", "");
              } else {
                bot.sendMessage(sender_id, "Ya se ha alcanzado el limite de usuarios o hubo algun error", "");
              }
            }/* else if (msg == "/reset" && sender == chat_ids[0]) {

            }*/ else {
              bot.sendMessage(sender_id, "Intenta escribir '/add <chat_id>'", "");
            }
          }
        } else {
          bot.sendMessage(sender_id, "Intenta escribiendo '/help'", "");
        }
        else {
          bot.sendMessage(chat_ids[0], "Se ha intentado unir un intruso", "");
        }
      }
      new_msg = bot.getUpdates(bot.last_message_received + 1);
    }
    lastCheck = millis();
  }
  server.handleClient();
}
