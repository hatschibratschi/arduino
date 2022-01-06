void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  delay(200);
  digitalWrite(LED_BUILTIN,HIGH);
  Serial.println("Blink");
  delay(800);
  digitalWrite(LED_BUILTIN,LOW);

}
