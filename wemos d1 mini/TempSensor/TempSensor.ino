/*                       
           _____
GND     --| DS  |  
DATA    --| 18. |
VDD 5v  --|_____|
*/

// OneWire lib:           https://www.pjrc.com/teensy/td_libs_OneWire.html
// DallasTemperature lib: https://github.com/milesburton/Arduino-Temperature-Control-Library

#include <OneWire.h>
#include <DallasTemperature.h>

// Der PIN D4 (GPIO 2) wird als BUS-Pin verwendet
#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);

// In dieser Variable wird die Temperatur gespeichert
float temperature;

void setup(){
  Serial.begin(115200);

  // DS18B20 initialisieren
  DS18B20.begin();
}

void loop(){
  
  DS18B20.requestTemperatures();
  temperature = DS18B20.getTempCByIndex(0);

  // Ausgabe im seriellen Monitor
  Serial.println(String(temperature) + " °C");

  // 5 Sekunden warten
  delay(5000);

}
