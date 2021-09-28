#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "Parser.h"
#include "VGACreator.h"


const char *ssid = "TicTacToe";
const char *password = "sdfhnedro654jtr34";

ESP8266WebServer my_server(80);
Parser parser;
VGACreator vga;
int aiGameField[9] = {0};
int iPlayerWon, iStartingField, iEndingField = -1;

void handleSentVar() {
  if (parser.parse(&my_server))
  {
    my_server.send(200, "text/html", "Data received");
    if (parser.getCurrentField(aiGameField))
    {
      vga.updateGameField(aiGameField);
    }
    if (parser.getPlayerWon(&iPlayerWon, &iStartingField, &iEndingField))
    {
      vga.playerWon(iPlayerWon, iStartingField, iEndingField);
    }
  }
  else
  {
    my_server.send(200, "text/html", "Invalid data received");
  }
}

void setup() {
  delay(1000);

  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  
  Serial.begin(115200);
  Serial.println(myIP);
  Serial.println("Successfull");

  my_server.on("/data/", HTTP_GET, handleSentVar); // when the my_server receives a request with /data/ in the string then run the handleSentVar function
  my_server.begin();
  vga.start();
}

void loop() {
  my_server.handleClient();
}