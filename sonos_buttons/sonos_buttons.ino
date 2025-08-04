// i use ARDUINO NANO 33 IoT
// change BOARD !and! PORT

#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>

#include "wifi_helper.h"
#include "secret.h" 
/* file with:
#define WIFI_SSID "your_ssid" 
#define WIFI_PASSWORD "your_pw"
*/

const int button_1 = 2; // digital pin 2 ...
const int button_2 = 3;
const int button_3 = 4;
const int button_4 = 5;
const int button_5 = 6;
const int button_6 = 7;
const int ledPin = LED_BUILTIN; // pin to use for the LED

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

const int station_array_size = 3;

// string array is station_name, station_url, station_image (does not work :-(  )
String oe1[station_array_size] = { "Österreich 1", "/play_fav/MyOe1", "" };
String soho_radio[station_array_size] = { "Soho Radio", "/play_fav/MySohoRadioMusic", "" };
String latte_miele[station_array_size] = { "Radio LatteMiele", "/play_fav/MyLatteMiele", "" };
String brum[station_array_size] = { "BrumRadio", "/play_fav/MyBrum", "" };
String dlf[station_array_size] = { "Deutschlandfunk", "/play_fav/MyDLF", "" };

int status = WL_IDLE_STATUS;

char server[] = "192.168.0.6"; // raspberry pi with sonos-python-server
int port = 8000;

String speaker = "kitchen";

WiFiClient wifi;
HttpClient client = HttpClient(wifi, server, port);

void setup() {
  Serial.begin(9600);

  // set LED pin to output mode
  pinMode(ledPin, OUTPUT);

  // configure the button pin as input
  pinMode(button_1, INPUT);
  pinMode(button_2, INPUT);
  pinMode(button_3, INPUT);
  pinMode(button_4, INPUT);
  pinMode(button_5, INPUT);
  pinMode(button_6, INPUT);
  digitalWrite(button_1, HIGH);
  digitalWrite(button_2, HIGH);
  digitalWrite(button_3, HIGH);
  digitalWrite(button_4, HIGH);
  digitalWrite(button_5, HIGH);
  digitalWrite(button_6, HIGH);

  connectToAP(ssid, password);
  printWifiStatus();
  Serial.println();
}

void loop() {
  digitalWrite(ledPin, LOW);

  if (digitalRead(button_1) == 0) {
    Serial.println("button 1 pressed");
    digitalWrite(ledPin, HIGH);
    web_request("/" + speaker, oe1[1], client);
  }
  if (digitalRead(button_2) == 0) {
    Serial.println("button 2 pressed");
    digitalWrite(ledPin, HIGH);
    web_request("/" + speaker, soho_radio[1], client);
  }
  if (digitalRead(button_3) == 0) {
    Serial.println("button 3 pressed");
    digitalWrite(ledPin, HIGH);
    web_request("/" + speaker, latte_miele[1], client);
  }
  if (digitalRead(button_4) == 0) {
    Serial.println("button 4 pressed");
    digitalWrite(ledPin, HIGH);
    web_request("/" + speaker, brum[1], client);
  }
  if (digitalRead(button_5) == 0) {
    Serial.println("button 5 pressed");
    digitalWrite(ledPin, HIGH);
    web_request("/" + speaker, dlf[1], client);
  }
  if (digitalRead(button_6) == 0) {
    Serial.println("button 6 pressed");
    digitalWrite(ledPin, HIGH);
    web_request("/" + speaker, "/pauseplay", client);
  }
}

void web_request(String path, String body, HttpClient client ) {
  Serial.println("POST request:");
  Serial.println(path + body);

  client.get(path + body);
  //client.get("/");

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();
  
  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
  Serial.println();
}
