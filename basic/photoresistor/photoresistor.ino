
const int sensorPin = 1; // pin to A1 on mkr 1010

int lightCal;

void setup(){
  Serial.begin(9600);
}

void loop() {
  lightCal = analogRead(sensorPin);
  Serial.println(lightCal);
  delay(1000);  
}
