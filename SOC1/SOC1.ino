
#include <Adafruit_NeoPixel.h>
#include <NewEEPROM.h>
#include <avr/sleep.h>

#define PIN 9
#define BUTTON 2
#define MIN 2
#define MAXPIXELS 28

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(MAXPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int program = 0;
int addr = 10;
int button = 0;
int change = 0;
int color = 0;

void setup() {
 
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pinMode(BUTTON,INPUT_PULLUP);
  
  button = digitalRead(BUTTON); 
  program = EEPROM.read(addr);
  color = EEPROM.read(addr+1);
  if (program > 7) {
    program = 0;}
    if ( !button){
    EEPROM.write(addr, ++program);
    }
     program = 6;
}

void loop() {
  
  switch (program){
    case 1: theaterChase(strip.Color(127, 127, 127), 100); break;
    case 2: colorWipeLoop(100); break;
    case 3: theaterChaseRainbow(100); break;
    case 4: rainbowCycle(30); break;
    case 5: rainbow(100); break;
    case 6: colorfadeLoop(10); break;
    case 7: police(500);
    default:  colorWipeButton(); break;
  }
  
}

void colorWipeButton(){
  button = digitalRead(BUTTON); 
 if ( !button){ 
 change = 1;
 color++;
 }
if(!button && change){
    EEPROM.write(addr+1, color);
 }
   colorWipe(Wheel(color), 2);
   change = 0;
}

void sleepnow(){
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
cli();
//sleep_bod_disable();
sei();
sleep_cpu();
}

void colorWipeLoop(uint8_t wait){

  colorWipe(strip.Color(255, 0, 0), wait); // Red
  colorWipe(strip.Color(0, 255, 0), wait); // Green
  colorWipe(strip.Color(0, 0, 255), wait); // Blue
}

void colorfadeLoop(uint8_t wait){
 #define MAX 200
  
      for(uint16_t i=0; i<MAX; i++) {
  colorStrip(strip.Color(MAX, i, 0), wait); // Red

  }
        for(uint16_t i=0; i<MAX; i++) {
  colorStrip(strip.Color(MAX-i, MAX, 0), wait); // Red

  }
  delay(4000);
    
        for(uint16_t i=0; i<MAX; i++) {
  colorStrip(strip.Color(0, MAX, i), wait); // Red

  }
          for(uint16_t i=0; i<MAX; i++) {
  colorStrip(strip.Color(0, MAX-i, MAX), wait); // Red

  }
  delay(4000);
            for(uint16_t i=0; i<MAX; i++) {
  colorStrip(strip.Color(i, 0, MAX), wait); // Red

  }
              for(uint16_t i=0; i<MAX; i++) {
  colorStrip(strip.Color(MAX, 0, MAX-i), wait); // Red

  }
  delay(4000);


}
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void colorPart(uint32_t c, uint8_t wait,uint8_t first, uint8_t last) {
  for(uint16_t i=first; i<last; i++) {
      strip.setPixelColor(i, c);
      delay(wait);
  }
}

void colorRotate(uint32_t c1, uint32_t c2){
    for(uint16_t i=0; i<1; i++) {
      colorPart(c1,0,0,7);
      colorPart(c2,0,7,14);
      colorPart(c1,0,14,21);
      colorPart(c2,0,21,29);
      strip.show();
  }
}

void police(uint8_t wait){
    for(uint16_t i=0; i<1; i++) {
      colorRotate(strip.Color(255, 0, 0), strip.Color(0, 0, 255));
      delay(wait);
      colorRotate(strip.Color(0, 0, 255), strip.Color(255, 0, 0));
      delay(wait);
  }
}

//void colorRotate(uint32_t c, uint8_t wait){
//  for(uint16_t i=0; i<4; i++) {
//      for(uint16_t i=0; i<strip.numPixels(); i++) {
//        strip.setPixelColor(i, 0);
//        if
//        st
//      strip.show();
//      delay(wait);
//  }
//}

void colorStrip(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
     // strip.show();
     // delay(wait);
  }
  strip.show();
  delay(wait);
}

void colorFade(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  int maxi= 127;
      for (int i=0; i < strip.numPixels(); i=i+3) {
        //strip.setPixelColor(i+q, c);    //turn every third pixel on
        for(uint16_t j=MIN; j<maxi; j++) {
          strip.setPixelColor(i+0, j,j,j);
          strip.show();
        }
      }
      //strip.show();
     
      delay(wait);
            for (int i=0; i < strip.numPixels(); i=i+3) {
      //  strip.setPixelColor(i+q, strip.Color(50, 50, 50));        //turn every third pixel off
        for(uint16_t j=0; j<maxi; j++) {
          strip.setPixelColor(i+2, MIN+(maxi-j),MIN+(maxi-j),MIN+(maxi-j));
          strip.show();
        }
      }
      delay(wait);
            for (int i=0; i < strip.numPixels(); i=i+3) {
        //strip.setPixelColor(i+q, c);    //turn every third pixel on
        for(uint16_t j=MIN; j<maxi; j++) {
          strip.setPixelColor(i+1, j,j,j);
          strip.show();
        }
      }
       delay(wait);
      for (int i=0; i < strip.numPixels(); i=i+3) {
       // strip.setPixelColor(i+q, strip.Color(50, 50, 50));        //turn every third pixel off
        for(uint16_t j=0; j<maxi; j++) {
          strip.setPixelColor(i+0,MIN+(maxi-j),MIN+(maxi-j),MIN+(maxi-j));
          strip.show();
        }
      }
      delay(wait);
                  for (int i=0; i < strip.numPixels(); i=i+3) {
        //strip.setPixelColor(i+q, c);    //turn every third pixel on
        for(uint16_t j=MIN; j<maxi; j++) {
          strip.setPixelColor(i+2, j,j,j);
          strip.show();
        }
      }
     delay(wait);
      for (int i=0; i < strip.numPixels(); i=i+3) {
      //  strip.setPixelColor(i+q, strip.Color(50, 50, 50));        //turn every third pixel off
        for(uint16_t j=0; j<maxi; j++) {
          strip.setPixelColor(i+1, MIN+(maxi-j),MIN+(maxi-j),MIN+(maxi-j));
          strip.show();
        }
      }
    delay(wait);
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

