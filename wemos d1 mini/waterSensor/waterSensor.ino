#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "secret.h" // file with: #define WIFI_PASSWORD "your_pw"

const char *password = WIFI_PASSWORD;
const char *ssid = WIFI_SSID;
const int sensor = A0;
const char *DEVICENAME = "wemosD1Mini";

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

void sendPost(int sendValue)
{
  WiFiClient wificlient;
  HTTPClient client;
  const uint16_t MESSAGE_SIZE_MAX = 300;                   // maximum bytes for Message Buffer
  char message[MESSAGE_SIZE_MAX];                          // the temporary sending message - html body
  char val[32];                                            // buffer to convert floats and integers before appending

  strcpy(message, "device=");                               // Append chars
  strcat(message, DEVICENAME);

  strcat(message, "&sensor=");
  strcat(message, "water");
  
  strcat(message, "&value=");
  itoa(sendValue, val, 10);
  strcat(message, val);
  
  client.begin(wificlient, "http://192.168.0.4:5762/saveSensorValue");
  client.addHeader("Content-Type", "application/x-www-form-urlencoded");       // Specify content-type header
  int httpCode = client.POST(message);                                         // Send the request
  client.writeToStream(&Serial);                                               // Debug only: Output of received data
  Serial.print(F("\nhttpCode: "));                                             
  Serial.println(httpCode);                                                    // Print HTTP return code
  Serial.println(message);                                                    // Print HTTP return code

  client.end();  //Close connection
}
void loop() {
  value = analogRead(sensor);  // This reads the analog in value
  
  // Then we can print the value read on the serial terminal window
  //Serial.print("sensor: ");
  //Serial.println(value);

  sendPost(value);
  waitMs = (10 * 60 * 1000) - 50; // 30 seconds
  
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED off (HIGH is the voltage level)
  delay(waitMs);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED on by making the voltage LOW
  delay(50);                       // wait for a second
}
