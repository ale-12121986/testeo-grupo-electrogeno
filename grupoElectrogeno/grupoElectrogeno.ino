#include <WiFi.h>
#include <WiFiClient.h>
//#include <ESPAsyncWebServer.h>
#include <WebServer.h>
#include "config.h"
//const char* ssid = "your_SSID";
//const char* password = "your_PASSWORD";

WebServer servidorWeb(80);
WiFiClient clienteWeb;

const int pinR = 2;
const int pinS = 4;
const int pinT = 5;
int pinR2 = 0;
int pinS2 = 0;
int pinT2 = 0;
const int pinGeneradorEncendido = 14;
const int pinGeneradorFallo = 12;
const int pinEncenderGenerador = 16;
const int pinApagarGenerador = 17;
int estado = 0;
String obtenerInterfaz(){

  String HtmlRespuesta = "<!DOCTYPE html>"  
                         "<html lang='en'>"
                         "<head>"
                         "<meta charset='UTF-8'>"
                         "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
                         "<title>Generador</title>"
                         "</head>"
                         "<body>";
  HtmlRespuesta += "<h2> Señal de la red</h2>";
  HtmlRespuesta += "<p> Señal de la red";
  if(estado == 1){
    HtmlRespuesta += "R </p>";

  }
  else if(estado == 2){
    HtmlRespuesta += "S </p>";

  }
  else if(estado == 3){
    HtmlRespuesta += "T </p>";
  }
  HtmlRespuesta +="</body>"
                  "</html>";

  return HtmlRespuesta;
}

void rutaRaiz()
{
  mostrarInterfazHTML();
}

void mostrarInterfazHTML()
{
  servidorWeb.send(200, "text/html", obtenerInterfaz());
}


void rutaNoEncontrada()
{
  servidorWeb.send(404, "text/plain", "404");
}

void senalRActiva(){

}

void senalSActiva(){

}

void senalTActiva(){

}
void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  pinMode(pinR, INPUT);
  pinMode(pinS, INPUT);
  pinMode(pinT, INPUT);
  pinMode(pinGeneradorEncendido, INPUT);
  pinMode(pinGeneradorFallo, INPUT);
  pinMode(pinEncenderGenerador, OUTPUT);
  pinMode(pinApagarGenerador, OUTPUT);

  //Se inicia la conexion WiFi
  Serial.print("Conectando a " + String(ssid) + " ");
  WiFi.config(ip,gateway,subnet);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  //Se inicia el servidor web

  servidorWeb.on("/",rutaRaiz);
  servidorWeb.on("/rActiva",senalRActiva);
  servidorWeb.on("/sActiva",senalSActiva);
  servidorWeb.on("/tActiva",senalTActiva);
  servidorWeb.on("/",rutaRaiz);
  servidorWeb.onNotFound(rutaNoEncontrada);
  servidorWeb.begin();
  Serial.println("Servidor web arrancado");
}

void loop() {
  // put your main code here, to run repeatedly:
  servidorWeb.handleClient();
  if (pinR == LOW && pinR2 == 0 ) {
    pinR2 = 1;
    pinS2 = 0;
    pinT2 = 0;
    estado = 1;
    mostrarInterfazHTML();
  }
  else if (pinS == LOW && pinS2 == 0 ) {
    pinR2 = 0;
    pinS2 = 1;
    pinT2 = 0;
    estado = 2;
  }
  else if (pinT == LOW && pinT2 == 0 ) {
    pinR2 = 0;
    pinS2 = 0;
    pinT2 = 1;
    estado = 3;
  }
  
}
