
#include <Adafruit_NeoPixel.h>
#define PIN 9
#define BUTTON 2
#define MIN 2
#define GAP 50
#define MARK 80
#define MAXPIXELS 28
Adafruit_NeoPixel strip = Adafruit_NeoPixel(MAXPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup(){

strip.begin();
  strip.show(); // Initialize all pixels to 'off'
pinMode(3, OUTPUT); 
   digitalWrite(3, LOW); 
pinMode(BUTTON,INPUT_PULLUP); 
}

void loop(){
   for(uint16_t i=0; i<5; i++) {
   strip.setPixelColor(i,strip.Color(0,255,0));
      strip.show();
   }
      delay(MARK);
     for(uint16_t j=0; j<5; j++) {
   strip.setPixelColor(j,strip.Color(0,0,0));
        
     }
     strip.show();
     delay(GAP);
    for(uint16_t i=0; i<5; i++) {
    strip.setPixelColor(0,strip.Color(0,255,0)); 
    strip.setPixelColor(5,strip.Color(0,255,0));
     strip.show();
   delay(MARK);
       for(uint16_t j=0; j<6; j++) {
   strip.setPixelColor(j,strip.Color(0,0,0));
        
     }
     strip.show();
     delay(GAP);
     
    }
    for(uint16_t i=0; i<6; i++) {
    strip.setPixelColor(i,strip.Color(0,0,0)); 
     }
      strip.show();
     delay(GAP);
}
  
  
