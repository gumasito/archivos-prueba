#include <WiFi.h>
#include "SPIFFS.h"
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
//#include "esp_task_wdt.h"


//#define WDT_TIMEOUT 10
#define MAX_USERS 10
#define CFG_OK (1<<0)

String ssid1, pass1, ssid2, pass2, port, server;
String resultados = "";
int var;
int current_users = 0;

EventGroupHandle_t events;
TaskHandle_t wifiTask;
unsigned long lastCheck = 0;

WiFiClientSecure client;
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
      Serial.println("Wifi Conectado con exito");
      Serial.println(WiFi.localIP());
    } else {
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
      Serial.println("Wifi conectado exitosamente");
      Serial.println(WiFi.localIP());
    }
  } else {
    Serial.println("Wifi conectado exitosamente");
    Serial.println(WiFi.localIP());
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
bool estadoPuerta(int sensor) {
  estadoPirPuerta = digitalRead(sensor);
  digitalWrite(luz_pir_puerta, estadoPirPuerta && !PIRCheck ? HIGH : LOW);

  PIRCheck = estadoPirPuerta;
  return estadoPirPuerta;
}
bool estadoGeneral() {
  return estadoLed1 && estadoLed2; // F & F = F - V & V = V - F & V = F
}
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
    1,
    &wifiTask,
    0);
  Serial.println("Conexion Exitosa");

  Serial.println(WiFi.macAddress());

}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    if (!moski.connected()) {
      connectMQTT();
    }
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
