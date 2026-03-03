#include <WiFi.h>
#include <UniversalTelegramBot.h>
#include "SPIFFS.h"
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
//#include "esp_task_wdt.h"


//#define WDT_TIMEOUT 10
#define MAX_USERS 10
#define CFG_OK (1<<0)
#define WIFI_OK (1<<1)

String telegramToken;
String chat_ids[MAX_USERS];
String ssid1, pass1, ssid2, pass2, port, server;
String resultados = "";
int var;
int current_users = 0;

EventGroupHandle_t events;
TaskHandle_t wifiTask;
TaskHandle_t telegramTask;
unsigned long lastCheck = 0;

WiFiClientSecure client;
UniversalTelegramBot* bot = nullptr; //puntero que busca la variable "bot" con los valores a utilizar
WiFiClient espClient;
PubSubClient moski(espClient);
//pines
const int led1 = 22;
const int led2 = 23;

const int sensor_pir_puerta = 34 ;
const int luz_pir_puerta = 21;

//estados
bool estadoLed1 = false;
bool estadoLed2 = false;

bool estadoPirPuerta = false; //Valor actual de lectura
bool PIRCheck = false; //Valor anterior de lectura
static unsigned long lastPIR = 0; //evitar debounce


void conectarWifi(void* pv) {

  xEventGroupWaitBits(
    events,
    CFG_OK,
    false,
    true,
    portMAX_DELAY);
  for (;;) {
    if (WiFi.status() == WL_CONNECTED) {
      xEventGroupSetBits(events, WIFI_OK);
    } else {
      xEventGroupClearBits(events, WIFI_OK);
      ensureWiFi();
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void ensureWiFi() {
  WiFi.begin(ssid1.c_str(), pass1.c_str());
  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startTime < 15000) {  // Wait up to 30s
    vTaskDelay(pdMS_TO_TICKS(300));
    Serial.print(".");
  }
  if (WiFi.status() != WL_CONNECTED) {
    // Fallback to secondary WiFi
    Serial.println("\nFallo en WiFi primario, intentando secundario...");
    WiFi.begin(ssid2.c_str(), pass2.c_str());
    startTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startTime < 15000) {
      vTaskDelay(pdMS_TO_TICKS(500));
      Serial.print(".");
    }
    if (WiFi.status() == WL_CONNECTED) {
      xEventGroupSetBits(events, WIFI_OK);
    }
  } else {
    xEventGroupSetBits(events, WIFI_OK);
  }
}
void conectarTelegram(void* pv) {
  xEventGroupWaitBits(
    events,
    WIFI_OK,
    false,
    true,
    portMAX_DELAY);
  for (;;) {
    if (telegramToken.length() > 0) {
      if (bot == nullptr) {
        client.setInsecure();
        bot = new UniversalTelegramBot(telegramToken, client); //si existe algun contenido en la variable en JSON, El objeto bot empieza.
        bot->longPoll = 4;
        Serial.println("Servidor Listo");
      }
    } else {
      Serial.println("Error al cargar telegramToken. Reiniciando...");
      ESP.restart();
    }
    initTelegram();
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
void initTelegram() {
  if (bot == nullptr)return;
  String script = "/led1: cocina - /led2: pasillo - /todo: todo - /estado: Estado de luces - /sensor: Puerta Casa";
  if (millis() - lastCheck > 4000) {
    int new_msg = bot->getUpdates(bot->last_message_received + 1);
    Serial.println(new_msg);
    if (new_msg) { // cambio de while a if para evitar consumo repetitivo de CPU
      for (int i = 0; i < new_msg; i++) {
        String msg = bot->messages[i].text;
        String sender_id = bot->messages[i].chat_id;
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
            bot->sendMessage(sender_id, script, "");
          } else if (msg == "/led1") {
            if (estadoLed1) {
              bot->sendMessage(sender_id, "Esta luz ya está prendida", "");
              ManejarLedNormal(1);  // cambia el estado
              bot->sendMessage(sender_id, "Ahora está apagada", "");
            } else {
              bot->sendMessage(sender_id, "Esta luz está apagada", "");
              ManejarLedNormal(1);
              bot->sendMessage(sender_id, "Ahora está prendida", "");
            }
          } else if (msg == "/led2") {
            if (estadoLed2) {
              bot->sendMessage(sender_id, "Esta luz ya está prendida", "");
              ManejarLedNormal(2);
              bot->sendMessage(sender_id, "Ahora está apagada", "");
            } else {
              bot->sendMessage(sender_id, "Esta luz está apagada", "");
              ManejarLedNormal(2);
              bot->sendMessage(sender_id, "Ahora está prendida", "");
            }
          }
          else if (msg == "/todo") {
            if (estadoGeneral()) {
              bot->sendMessage(sender_id, "Está todo prendido", "");
              ManejarTodoNormal();
              bot->sendMessage(sender_id, "Ahora está todo apagado", "");
            } else {
              bot->sendMessage(sender_id, "Está todo apagado", "");
              ManejarTodoNormal();
              bot->sendMessage(sender_id, "Ahora está todo prendido", "");
            }
          } else if (msg == "/estado") {
            bot->sendMessage(sender_id, mensaje, "");
          } else if (msg == "/sensor") {
            if (estadoPuerta(sensor_pir_puerta)) {
              bot->sendMessage(sender_id, "Hay Alguien", "");
            } else {
              bot->sendMessage(sender_id, "No Hay Nadie", "");
            }
          } else if (msg.startsWith("/add") && sender_id == chat_ids[0]) {
            int espacio = msg.indexOf(" ");
            if (espacio != -1) {
              String nuevoID = msg.substring(espacio + 1);
              if (agregarUsuario(nuevoID)) {
                saveConfig();
                bot->sendMessage(sender_id, "Usuario " + nuevoID + " fue agregado exitosamente", "");
              } else {
                bot->sendMessage(sender_id, "Ya se ha alcanzado el limite de usuarios o hubo algun error", "");
              }
            }/* else if (msg == "/reset" && sender == chat_ids[0]) {

            }*/ else {
              bot->sendMessage(sender_id, "Intenta escribir '/add <chat_id>'", "");
            }
          }
          else {
            bot->sendMessage(sender_id, "Intenta escribiendo '/help'", "");
          }
        }
        else {
          bot->sendMessage(chat_ids[0], "Se ha intentado unir un intruso", "");
        }
      }
    }
    lastCheck = millis();
  }
}

bool loadConfig() {
  File conf = SPIFFS.open("/config.json", "r");
  if (!conf) {
    Serial.println("Error al abrir config.json");
    return false;
  }
  StaticJsonDocument<2048> docConf;
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
    if (current_users >= MAX_USERS)break;

    chat_ids[current_users++] = id;
  }
  ssid1 = docConf["wifi"]["ssid"].as<String>();
  pass1 = docConf["wifi"]["pass"].as<String>();
  ssid2 = docConf["wifi"]["ssid2"].as<String>();
  pass2 = docConf["wifi"]["pass2"].as<String>();
  server = docConf["mqtt"]["server_ip"].as<String>();
  port = docConf["mqtt"]["port"].as<String>();
  xEventGroupSetBits(events, CFG_OK);
  return true;
}
void saveConfig() {
  StaticJsonDocument<2048> doc;

  JsonArray ids = doc.createNestedObject("telegram").createNestedArray("chat_ids");
  for (int i = 0; i < current_users; i++) {
    ids.add(chat_ids[i]);
  }

  doc["telegram"]["token"] = telegramToken;

  doc["wifi"]["ssid"] = ssid1;
  doc["wifi"]["pass"] = pass1;
  doc["wifi"]["ssid2"] = ssid2;
  doc["wifi"]["pass2"] = pass2;
  doc["mqtt"]["server_ip"] = server;
  doc["mqtt"]["port"] = port;
  File file = SPIFFS.open("/config.json", "w");
  serializeJson(doc, file);
  file.close();
}
void callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }
  String top = String(topic);
  if (top == "prueba/led/cmd") {
    if (msg == "ON") {
      digitalWrite(led1, HIGH);
      estadoLed1 = true;
      moski.publish("prueba/led/state", "ON", true);
    } else if (msg == "OFF") {
      digitalWrite(led1, LOW);
      estadoLed1 = false;
      moski.publish("prueba/led/state", "OFF", true);
    }
  } else if (top == "prueba/led2/cmd") {
    if (msg == "ON") {
      digitalWrite(led2, HIGH);
      estadoLed2 = true;
      moski.publish("prueba/led2/state", "ON", true);
    } else if (msg == "OFF") {
      digitalWrite(led2, LOW);
      estadoLed2 = false;
      moski.publish("prueba/led2/state", "OFF", true);
    }
  } else if (top == "prueba/todo/cmd") {
    if (msg == "ON") {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      estadoLed1 = true;
      estadoLed2 = true;
      moski.publish("prueba/todo/state", "ON", true);
    } else if (msg == "OFF") {
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      estadoLed1 = false;
      estadoLed2 = false;
      moski.publish("prueba/todo/state", "OFF", true);
    }
  }
}

void connectMQTT() {
  moski.setServer(server.c_str(), port.toInt());
  moski.setCallback(callback);

  while (!moski.connected()) {
    Serial.print("Conectando MQTT...");
    if (moski.connect("ESP32_LED", "gumasito", "Lauralp21.love/22")) {
      Serial.println("OK");
      moski.subscribe("prueba/led/cmd");
      moski.subscribe("prueba/led2/cmd");
      moski.subscribe("prueba/todo/cmd");
      moski.publish("prueba/led/state", "OFF", true);
      moski.publish("prueba/led2/state", "OFF", true);
      moski.publish("prueba/todo/state", "OFF", true);

    } else {
      Serial.print("Fallo rc=");
      Serial.println(moski.state());
      delay(2000);
    }
  }
}
void SendMessageToAll(String message) {
  if (bot == nullptr)return;
  for (int i = 0; i < current_users; i++) {
    bot->sendMessage(chat_ids[i], message, "");
  }
}

bool estadoPuerta(int sensor) {
  estadoPirPuerta = digitalRead(sensor);
  digitalWrite(luz_pir_puerta, estadoPirPuerta && !PIRCheck ? HIGH : LOW);

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
  /*chat_ids[numUsers] = nuevoID;
    numUsers++;
    es lo mismo*/
  return true;
}
bool estadoGeneral() {
  return estadoLed1 && estadoLed2; // F & F = F - V & V = V - F & V = F
}
/*========================================================
  ==Esto no es para HTTP, sino que es para telegram + MQTT==
  ==========================================================
  ==========================================================*/
void ManejarTodoNormal() {
  bool nuevoValor = !estadoGeneral(); // F = V - V = F

  estadoLed1 = nuevoValor;
  estadoLed2 = nuevoValor;

  digitalWrite(led1, estadoLed1);
  digitalWrite(led2, estadoLed2);
}
void ManejarLedNormal(int num) {
  if (num == 1) {
    estadoLed1 = !estadoLed1;
    digitalWrite(led1, estadoLed1);
  }
  else if (num == 2) {
    estadoLed2 = !estadoLed2;
    digitalWrite(led2, estadoLed2);
  }
}
String Users(String user) {
  if (chat_ids[0] == user) {
    return "admin";
  } else if (current_users > 1 && chat_ids[1] == user) {
    return "user1";
  }
  return "desconocido";
}
void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  pinMode(sensor_pir_puerta, INPUT);
  pinMode(luz_pir_puerta, OUTPUT);
  digitalWrite(luz_pir_puerta, LOW);
  events = xEventGroupCreate();
  /*esp_task_wdt_init(WDT_TIMEOUT, true);
    esp_task_wdt_add(NULL);*/
  if (!SPIFFS.begin(true)) {
    Serial.println("Error montando SPIFFS");
  }
  if (!loadConfig()) {
    Serial.println("Error con loadConfig");//funcion para manejar datos de los spiffs de las variables de telegram y conexion a la red
  }
  xTaskCreatePinnedToCore(
    conectarWifi,
    "Task Wifi",
    4096,
    NULL,
    2,
    &wifiTask,
    0);
  xTaskCreatePinnedToCore(
    conectarTelegram,
    "Task Telegram",
    4096,
    NULL,
    1,
    &telegramTask,
    1);
    if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConexion Exitosa");
    Serial.println(WiFi.localIP());
    xEventGroupSetBits(events, WIFI_OK); // Print IP for web access
  }
  if (telegramToken.length() == 0) {
    Serial.println("Error con el token de telegram");
    ESP.restart();
  }
  Serial.println("Conexion Exitosa");

  Serial.println(WiFi.macAddress());

}

void loop() {
  if (!moski.connected()) {
    connectMQTT();
  }
  moski.loop();
  //esp_task_wdt_reset();
  if (millis() - lastPIR > 500) {
    estadoPuerta(sensor_pir_puerta);
    lastPIR = millis();
  }
}

/*Despues al agregar mas luces, se segmenta por habitaciones y no por general, luego, una variable
  por partes se comparan con otras por los comparadores. Asi se llega a la variable general.
  En la pagina web se pone un boton para poner por habitaciones y prender y apagar todo desde la app*/
