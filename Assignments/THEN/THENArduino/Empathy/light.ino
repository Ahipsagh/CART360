// Simple NeoPixel test.  Lights just a few pixels at a time so a
// 1m strip can safely be powered from Arduino 5V pin.  Arduino
// may nonetheless hiccup when LEDs are first connected and not
// accept code.  So upload code first, unplug USB, connect pixels
// to GND FIRST, then +5V and digital pin 6, then re-plug USB.
// A working strip will show a few pixels moving down the line,
// cycling between red, green and blue.  If you get no response,
// might be connected to wrong end of strip (the end wires, if
// any, are no indication -- look instead for the data direction
// arrows printed on the strip).

#include <Adafruit_NeoPixel.h>

#define PIN   6
#define N_LEDS 8


Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

int colourRed = 0; 
int colourGreen = 0;
int colourBlue = 0;

void setupLIGHT() {
  strip.begin();
//}

//void loop() {

if ( gsr >= 400 && gsr <=1023){
      Serial.println("RED");
      colourRed=255;
      colourGreen=0;
      colourBlue=0;
} else
       if ( gsr >= 250 && gsr <=399) {
    Serial.println("green");
        colourRed=0;
      colourGreen=255;
      colourBlue=0;
  //   chase(strip.Color(0, 255, 0)); // Green
    
 
 } else
 
    if ( gsr >= 101 && gsr <=249){
    Serial.println("blue");
          colourRed=0;
      colourGreen=0;
      colourBlue=255;
//      chase(strip.Color(0, 0, 255)); // Blue
    } else
     if ( gsr <=100) {
    Serial.println("NO Light");
//        chase(strip.Color(0, 0, 0)); // no light
}
chase(strip.Color(colourRed, colourGreen, colourBlue)); // show strip
}

static void chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
      strip.show();
      delay(50);
  }
}
