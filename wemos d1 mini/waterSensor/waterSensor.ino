#include <ESP8266WiFi.h>
#include "secret.h" // file with: #define WIFI_PASSWORD "your_pw"

const char *password = WIFI_PASSWORD;
const char *ssid = WIFI_SSID;
const int sensor = A0;

int value = 0;
int waitMs = 5000;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

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

void loop() {
  value = analogRead(sensor);  // This reads the analog in value
  
  // Then we can print the value read on the serial terminal window
  Serial.print("sensor: ");
  Serial.println(value);
  if(value < 50){
    waitMs = 200;
  }
  else if (value < 100){
    waitMs = 500;
  }
  else if (value < 150){
    waitMs = 1000;
  }
  else if (value < 200){
    waitMs = 4000;
  }
  else {
    waitMs = 6000;
  }
  
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED off (HIGH is the voltage level)
  delay(waitMs);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED on by making the voltage LOW
  delay(50);                       // wait for a second
}
