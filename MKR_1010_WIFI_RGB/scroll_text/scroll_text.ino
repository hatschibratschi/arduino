#include <ArduinoGraphics.h> // Arduino_MKRRGB depends on ArduinoGraphics
#include <Arduino_MKRRGB.h>

void setup() {
  // initialize the display
  MATRIX.begin();

  // set the brightness, supported values are 0 - 255
  MATRIX.brightness(5);

  // configure the text scroll speed
  MATRIX.textScrollSpeed(100);

  // display some short text without scrolling
  MATRIX.beginText(0, 0, 60, 0, 0); // X, Y, then R, G, B
  MATRIX.print("Hi");
  MATRIX.endText();

  delay(1000);
}

void loop() {
  MATRIX.beginText(MATRIX.width() - 1, 0); // use the same color as before, start text at the right edge
  MATRIX.print("millis=");
  MATRIX.println(millis());
  MATRIX.endText(SCROLL_LEFT); // SCROLL_LEFT parameter here to configure scrolling left
}
