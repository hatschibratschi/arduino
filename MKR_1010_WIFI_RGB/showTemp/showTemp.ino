/*         _____
GND     --| DS  |  
DATA    --| 18. |
VDD 5v  --|_____|
*/

// OneWire lib:           https://www.pjrc.com/teensy/td_libs_OneWire.html
// DallasTemperature lib: https://github.com/milesburton/Arduino-Temperature-Control-Library
#include <OneWire.h>
#include <DallasTemperature.h>

// Use PIN D4, GPIO 2 as BUS-Pin
#define ONE_WIRE_BUS 16
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
float temperature;

void setup(){
  Serial.begin(115200);

  DS18B20.begin();
}

void loop(){

  DS18B20.requestTemperatures();
  temperature = DS18B20.getTempCByIndex(0);
  Serial.println(String(temperature) + " °C");
  delay(1000);

}
