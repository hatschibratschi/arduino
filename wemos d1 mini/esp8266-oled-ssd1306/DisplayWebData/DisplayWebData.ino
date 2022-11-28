#include <Wire.h>               // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h"        // legacy: #include "SSD1306.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "secret.h" // file with: #define WIFI_PASSWORD "your_pw"

SSD1306Wire display(0x3c, SDA, SCL, GEOMETRY_64_48);   // ADDRESS, SDA, SCL  -  SDA and SCL usually populate automatically based on your board's pins_arduino.h e.g. https://github.com/esp8266/Arduino/blob/master/variants/nodemcu/pins_arduino.h

const char *password = WIFI_PASSWORD;
const char *ssid = WIFI_SSID;

int displayHeight = 48;
int displayWidth  = 64;

int sleepTimer = 10; // minutes
int refreshRate = 8; // seconds
int maxSleepTimer = sleepTimer * 60 / refreshRate;
int sleepTimerCounter = 0;

void writeToDisplay(String s){
  display.clear();
  display.drawStringMaxWidth(0, 0, displayWidth, s);
  display.display();
}

String SONOSgetData(String key, String s){
  // find first appearence of key
  int index = s.indexOf(key);
  if (index == -1){
    return "";
  }
  String sub = s.substring(index + key.length(), s.length());
  // find first line break
  index = sub.indexOf("\\n");
  sub = sub.substring(1, index);
  sub.trim();
  Serial.println(sub);
  return sub;
}

void setup() {
  Serial.begin(115200);

  // Initialising the UI will init the display too.
  display.init();
  display.flipScreenVertically();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);

  // WIFI
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  writeToDisplay("searching WIFI ...");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  writeToDisplay("IP: " + WiFi.localIP().toString());
}

void loop() {
  if(sleepTimerCounter < maxSleepTimer){
    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://192.168.0.6:8000/kitchen/track")) {  // HTTP


      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
          String t = SONOSgetData("Channel:", payload);
          if (t.length() > 0 & t != "Spotify"){
            // radio
            t = t + "\n" + SONOSgetData("Elapsed:", payload);
            writeToDisplay(t);
          } else {
            t = SONOSgetData("Title:", payload);
            t = t + "\nby " + SONOSgetData("Artist:", payload);
            writeToDisplay(t);
          }
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        writeToDisplay("HTTP Error:" + http.errorToString(httpCode));
      }
      http.end();
    }
  
    delay(refreshRate * 1000);
    
  } else {
    sleepTimerCounter = maxSleepTimer;
    Serial.println(sleepTimerCounter);
    display.clear();
    display.display();
    delay(100 * 1000);
  }
  sleepTimerCounter = sleepTimerCounter + 1;
}
