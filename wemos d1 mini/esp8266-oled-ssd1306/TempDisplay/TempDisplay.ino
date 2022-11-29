/*         _____
GND     --| DS  |  
DATA    --| 18. |
VDD 5v  --|_____|
*/

// OneWire lib:           https://www.pjrc.com/teensy/td_libs_OneWire.html
// DallasTemperature lib: https://github.com/milesburton/Arduino-Temperature-Control-Library
#include <OneWire.h>
#include <DallasTemperature.h>

// display
#include "SSD1306Wire.h"        // legacy: #include "SSD1306.h"

// Der PIN D4 (GPIO 2) wird als BUS-Pin verwendet
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
// In dieser Variable wird die Temperatur gespeichert
float temperature;

SSD1306Wire display(0x3c, SDA, SCL, GEOMETRY_64_48);   // ADDRESS, SDA, SCL  -  SDA and SCL usually populate automatically based on your board's pins_arduino.h e.g. https://github.com/esp8266/Arduino/blob/master/variants/nodemcu/pins_arduino.h
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

void setup(){
  Serial.begin(115200);

  // Initialising the UI will init the display too.
  display.init();
  display.flipScreenVertically();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);

  // DS18B20 initialisieren
  DS18B20.begin();
}

void loop(){
  if(sleepTimerCounter < maxSleepTimer){
  
    DS18B20.requestTemperatures();
    temperature = DS18B20.getTempCByIndex(0);
  
    // Ausgabe im seriellen Monitor
    Serial.println(String(temperature) + " °C");
    writeToDisplay(String(temperature) + " °C");
    
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
