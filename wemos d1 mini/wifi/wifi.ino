#include <ESP8266WiFi.h>
#include "secret.h" // file with: #define WIFI_PASSWORD "your_pw"

const char *password = WIFI_PASSWORD;
const char *ssid = WIFI_SSID;

void setup()
{
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(ssid, password);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {}
