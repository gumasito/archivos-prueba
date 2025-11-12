#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "";
const char* password = "";

const int pinLed1 = 23;
const int pinLed2 = 22;

WebServer server(80);

bool estadoLed1 = false;
bool estadoLed2 = false;

bool estadoGeneral() {
  return estadoLed1 && estadoLed2;
}
void manejarTodo() {
  bool nuevaData = !estadoGeneral();
  estadoLed1 = nuevaData;
  estadoLed2 = nuevaData;
  digitalWrite(pinLed1, estadoLed1);
  digitalWrite(pinLed2, estadoLed2);
  server.send(200, "text/plain", nuevaData ? "Estan encendidos" : "Estan apagados");
}
void manejarLed1() {
  estadoLed1 = !estadoLed1;
  digitalWrite(pinLed1, estadoLed1);
  server.send(200, "text/plain", estadoLed1 ? "Esta encendido n°1" : "Esta apagado n°1");
}
void manejarLed2() {
  estadoLed2 = !estadoLed2;
  digitalWrite(pinLed2, estadoLed2);
  server.send(200, "text/plain", estadoLed2 ? "Esta encendido n°2" : "Esta encendido n°2");
}
void manejarEstado(){
  String json = "{";
  json += "\"general\":\"" + String(estadoGeneral() ? "Estan encendidos" : "Estan apagados") + "\",";
  json += "\"led1\":\"" + String(estadoLed1 ? "Esta encendido n°1" : "Esta apagado n°1") + "\",";
  json += "\"led2\":\"" + String(estadoLed2 ? "Esta encendido n°2" : "Esta apagado n°2") + "\"";
  json += "}";
  server.send(200,"application/json",json);
}
void manejarRoot() {
  String html = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
  <meta charset="UTF-8">
  <title>Prueba Propia</title>
  </head>
  <body>
  
  <h2>Lucesitas</h2>
  
  <p><b>Todo:</b> <span id="estadoGeneral">Desconocido</span></p>
  <button onclick="ControlarTodo()">Encender/Apagar Todo</button><br>
  
  <p><b>Led 1:</b> <span id="estadoLed1">Desconocido</span></p>
  <button onclick="ControlarLed1()">Encender/Apagar Led1</button><br>
  
  <p><b>Led 2:</b> <span id="estadoLed2">Desconocido</span></p>
  <button onclick="ControlarLed2()">Encender/Apagar Led2</button><br>
  
  <script>
  function ControlarTodo(){
    fetch("/todo")
      .then(res => res.text())
      .then(data => {
        document.getElementById("estadoGeneral").innerText = data;
        ActualizarTodosLosElementos();
      });
  }
  function ControlarLed1(){
    fetch("/uno")
      .then(res => res.text())
      .then(data => {
        document.getElementById("estadoLed1").innerText = data;
        ActualizarTodosLosElementos();
      });
    }
    function ControlarLed2(){
      fetch("/dos")
        .then(res => res.text())
        .then(data => {
          document.getElementById("estadoLed2").innerText = data;
          ActualizarTodosLosElementos();
        });
    }
    function ActualizarTodosLosElementos(){
      fetch("/estado")
        .then(res => res.json())
        .then(data => {
          document.getElementById("estadoGeneral").innerText = data.general;
          document.getElementById("estadoLed1").innerText = data.led1;
          document.getElementById("estadoLed2").innerText = data.led2;
        });
    }
    ActualizarTodosLosElementos();
   </script>
   </body>
   </html>
   )rawliteral";
   
  server.send(200, "text/html", html);
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(pinLed1,OUTPUT);
  pinMode(pinLed2,OUTPUT);

  digitalWrite(pinLed1,LOW);
  digitalWrite(pinLed2,LOW);
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println("Conexion Exitosa :) ");
  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.localIP());

  server.on("/",manejarRoot);
  server.on("/todo",manejarTodo);
  server.on("/uno",manejarLed1);
  server.on("/dos",manejarLed2);
  server.on("/estado",manejarEstado);
  server.begin();
  Serial.println("Servidor Listo");
}

void loop() {
  // put your main code here, to run repeatedly:
 server.handleClient();
}
