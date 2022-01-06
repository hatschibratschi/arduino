// Arduino MKR 1010 WIFI

#include <SPI.h>
#include <WiFiNINA.h>
#include "secret.h" // file with: #define WIFI_PASSWORD "your_pw"
#include "wifi_helper.h"

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

void setup()
{
  Serial.begin(9600);

  connectToAP(ssid, password);
  printWifiStatus();  
}

void loop() {}
