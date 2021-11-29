// audio input signal processing

// audio in
// 10uF capacitor per channel(left/right)
// 100k resistor per channel
// to analog 0 and 1 (A0, A1)

int audioRight;
int audioLeft;

void setup() {
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  delay(1);                       // wait for a second
  audioRight = analogRead(A0);  //read input from A0
  audioLeft = analogRead(A1);   //read input from A1
  Serial.print(audioRight);
  Serial.print(",");
  Serial.println(audioLeft);
}
