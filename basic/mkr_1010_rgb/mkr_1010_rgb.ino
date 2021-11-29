#include <WiFiNINA.h>
#include <utility/wifi_drv.h>

// light up on-board rgb of mkr-1010

void setup() {
  WiFiDrv::pinMode(25, OUTPUT); //define green pin6  
  WiFiDrv::pinMode(26, OUTPUT); //define red pin7  
  WiFiDrv::pinMode(27, OUTPUT); //define blue pin8
}
void loop() {
  WiFiDrv::analogWrite(25, 50);
  WiFiDrv::analogWrite(26, 0);
  WiFiDrv::analogWrite(27, 0);
  delay(1000);
  WiFiDrv::analogWrite(25, 0);
  WiFiDrv::analogWrite(26, 50);
  WiFiDrv::analogWrite(27, 0);
  delay(1000);
  WiFiDrv::analogWrite(25, 0);
  WiFiDrv::analogWrite(26, 0);
  WiFiDrv::analogWrite(27, 50);
  delay(1000);
}
