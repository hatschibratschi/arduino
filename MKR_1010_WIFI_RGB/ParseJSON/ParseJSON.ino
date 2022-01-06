// Arduino MKR 1010 WIFI

#include <SPI.h>
#include <WiFiNINA.h>

#include <ArduinoHttpClient.h> // https://github.com/arduino-libraries/ArduinoHttpClient/blob/master/examples/DweetGet/DweetGet.ino
#include <ArduinoJson.h>

#include <ArduinoGraphics.h> // Arduino_MKRRGB depends on ArduinoGraphics
#include <Arduino_MKRRGB.h>

#include "secret.h" // file with: #define WIFI_PASSWORD "your_pw"
#include "wifi_helper.h"

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

char serverAddress[] = "192.168.0.6";  // server address
int port = 8000;

void setup()
{
  Serial.begin(9600);

  IPAddress ip(192, 168, 0, 9);
  
  connectToAP(ssid, password, ip);
  printWifiStatus();  
}

void loop() {
  // initialize the display
  MATRIX.begin();

  // set the brightness, supported values are 0 - 255
  MATRIX.brightness(5);

  // configure the text scroll speed
  MATRIX.textScrollSpeed(100);

  // display some short text without scrolling
  MATRIX.beginText(0, 0, 60, 0, 0); // X, Y, then R, G, B
  MATRIX.print("");
  MATRIX.endText();
  
  WiFiClient wifi;
  HttpClient client = HttpClient(wifi, serverAddress, port);

  // assemble the path for the GET message:
  String path = "/kitchen/track"; 

  // send the GET request
  Serial.println("making GET request");
  client.get(path);

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();
  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

  // Parse response
  DynamicJsonDocument doc(2048);
  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, response);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  const char* result = doc["result"];
 
  //result = strtok(result, "\n");
  String msg = String(result);
  if(msg.indexOf("Playback is stopped") == -1 && msg.indexOf("Playback is paused") == -1 ){
    msg.replace("\n", " ");
    msg.replace("   ", " ");
    msg.replace("Playback is in progress:", "");
    msg.replace("Channel:", "");
    msg.replace("Radio Show: ", "");
    msg.replace("Artist:","");
    //msg.replace("Album: ","");
    //msg.replace("Title: ","");
    msg.replace("","");
    msg.replace("","");
    msg.replace("","");

    msg = removeEnd(msg, "Elapsed:");
    msg = removeEnd(msg, "Playlist Position:");   
    msg.trim();
    
    Serial.println(msg);

    MATRIX.beginText(MATRIX.width() - 1, 0); // use the same color as before, start text at the right edge
    MATRIX.println(msg);
    MATRIX.endText(SCROLL_LEFT); // SCROLL_LEFT parameter here to configure scrolling left
  }

  client.stop();
  Serial.println("delay for n seconds");
  delay(10000);
}

String removeEnd (String s, String r){
    if(s.indexOf(r) > 0){
      s = s.substring(1, s.indexOf(r));
    }
    return(s);
}
