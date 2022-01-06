// Arduino NANO 33 IOT

#include <SPI.h>
#include <WiFi101.h>
#include "secret.h" // file with: #define WIFI_PASSWORD "your_pw"
#include "wifi_helper.h"

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

void setup()
{
  Serial.begin(9600);
  Serial.println();

  connectToAP(ssid, password);
  printWifiStatus();  
}

void loop() {}
