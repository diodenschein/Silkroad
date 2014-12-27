
#include <Adafruit_NeoPixel.h>
#define PIN 9
#define BUTTON 2
#define MIN 2
#define GAP 2
#define MARK 100
#define MAXPIXELS 28
Adafruit_NeoPixel strip = Adafruit_NeoPixel(MAXPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup(){

strip.begin();
  strip.show(); // Initialize all pixels to 'off'


}

void loop(){
   for(uint16_t i=0; i<7; i++) {
   strip.setPixelColor(i,strip.Color(0,255,0));
      strip.show();
   }
      delay(3*MARK);
     for(uint16_t j=0; j<7; j++) {
   strip.setPixelColor(j,strip.Color(0,0,0));
        strip.show();
   
     }
     delay(GAP);
    strip.setPixelColor(1,strip.Color(0,255,0)); 
    strip.setPixelColor(7,strip.Color(0,255,0));
     strip.show();
   delay(MARK);
    for(uint16_t i=0; i<7; i++) {
    strip.setPixelColor(i,strip.Color(0,0,0));
        strip.show();
   
     }
     delay(GAP);
}
  
  
