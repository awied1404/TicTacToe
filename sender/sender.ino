#include <ESP8266WiFi.h>
#include "SerialRead.h"

const char *ssid = "TicTacToe";
const char *password = "sdfhnedro654jtr34";
SerialRead serialRead;

char acGameFields[9] = {0};
int iPlayerWon, iStartingField, iEndingField = 0;
void setup() {
  Serial.begin(115200);
  delay(10);

  // Explicitly set the ESP8266 to be a WiFi-client
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const char * host = "192.168.4.1";
  const int httpPort = 80;

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  if (serialRead.read())
  {
    String url = "/data/";
    serialRead.getGameFields(acGameFields);
    url += "?game_field=";
    url += acGameFields;
    if (serialRead.getWinner(&iPlayerWon, &iStartingField, &iEndingField))
    {
      char acBuffer[50] = {0};
      snprintf(acBuffer, 50, "?player_won=%i?start_field=%i?end_field=%i", iPlayerWon, iStartingField, iEndingField);
      url += acBuffer;
    }
        // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" +
                "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }
  }
}
