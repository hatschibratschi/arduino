void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("test");
  delay(1000);        // delay in between reads for stability
}
