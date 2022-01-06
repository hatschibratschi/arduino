void setup() {
  Serial.begin(9600);

}

void loop() {

  //if(content.indexOf("Teststring") > 0)
  const char* result = {"bla"};
  
  String message = "\n\tThis is one messed-up string  \r\n test \n 123 ";
  Serial.println(message);
  message.replace("\n", " ");
  Serial.println(message);
  Serial.println();
  delay(5000);
}
