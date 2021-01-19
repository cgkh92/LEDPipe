// SimpleRotary - Version: Latest 
#include <SimpleRotary.h>

// Pin A, Pin B, Button Pin
SimpleRotary rotary(0,1,10);

// FastLED - Version: Latest 
#include <FastLED.h>


#define NUM_LEDS 60
CRGB leds[NUM_LEDS];
#define PIN1 11

float t;
uint16_t it;
// how fast to run
float lspeed =1.0;

/* power up values */
int palette = 3 ;
int intensity = 120;
int bscale = 6;
int scale = 5;

int paletteChangeTimer;
#define PALETTE_CHANGE_TIME 10

#define NUM_PALETTES 6

// Gradient palette "serendil_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/rc/tn/serendil.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE( serendil_gp ) {
    0,   0, 55,  0,
  117,  61, 81,  9,
  137, 132, 86, 10,
  191, 215,221, 42,
  211, 237,112,184,
  255, 192, 19, 19};



// Gradient palette "yule_ribbons_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/pj/3/tn/yule-ribbons.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 84 bytes of program space.

DEFINE_GRADIENT_PALETTE( yule_ribbons_gp ) {
    0, 255,255,255,
   12, 217,  3,  3,
   20, 217,  3,  3,
   30, 255,255,255,
   48, 255,255,255,
   63,   7,101, 15,
   73,   7,101, 15,
   89, 255,255,255,
  101, 255,255,255,
  114, 217,  3,  3,
  122, 217,  3,  3,
  135, 255,255,255,
  145, 255,255,255,
  160,   7,101, 15,
  168,   7,101, 15,
  183, 255,255,255,
  196, 255,255,255,
  214, 217,  3,  3,
  219, 217,  3,  3,
  237, 255,255,255,
  255, 255,255,255};


// Gradient palette "dragon_foot_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/neota/othr/tn/dragon-foot.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 92 bytes of program space.

DEFINE_GRADIENT_PALETTE( dragon_foot_gp ) {
    0,   0,  0,  0,
   36,   1,  4,  2,
   73,   1, 22, 13,
   84,   4, 28, 15,
   94,   8, 34, 19,
  106,  10, 45, 23,
  117,  12, 57, 28,
  124,  16, 65, 31,
  132,  21, 72, 35,
  146,  32, 88, 43,
  161,  46,107, 52,
  166,  56,112, 59,
  171,  67,117, 65,
  180,  75,135, 65,
  190,  84,152, 66,
  197,  94,166, 66,
  204, 104,180, 65,
  214, 126,195, 78,
  224, 153,213, 91,
  235, 188,229,117,
  246, 227,248,145,
  250, 242,250,197,
  255, 255,255,255};



// Gradient palette "rainbow_sunset_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/neota/othr/tn/rainbow-sunset.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 68 bytes of program space.

DEFINE_GRADIENT_PALETTE( rainbow_sunset_gp ) {
    0,   0,  0,  0,
   16,   1,  1,  1,
   32,   1,  1,  1,
   48,   1,  1,  8,
   65,   1,  1, 21,
   81,   4,  3, 12,
   97,  13,  6,  6,
  114,  26,  5, 16,
  130,  44,  4, 32,
  143,  67, 15, 19,
  156,  97, 33,  9,
  169, 103, 56, 10,
  182, 110, 86, 10,
  201, 140,121, 37,
  220, 175,161, 88,
  237, 213,205,158,
  255, 255,255,255};


// Gradient palette "carousel_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/rc/tn/carousel.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( carousel_gp ) {
    0,   2,  6, 37,
  101,   2,  6, 37,
  122, 177,121,  9,
  127, 217,149,  2,
  132, 177,121,  9,
  153,  84, 13, 36,
  255,  84, 13, 36};


// Gradient palette "Caribbean_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/vh/tn/Caribbean.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 144 bytes of program space.

DEFINE_GRADIENT_PALETTE( Caribbean_gp ) {
    0,   0,  0, 43,
   24,   0,  5, 85,
   36,   0, 10,106,
   48,   1, 22,130,
   60,   1, 32,147,
   72,   1, 57,138,
   84,   1, 79,138,
   97,   1, 91,147,
  109,   3,104,156,
  121,  12,104,166,
  133,  17,118,176,
  133,  17,118,138,
  145,  35,118,176,
  157,  64,118,176,
  170,  82,133,156,
  182,  88,149,186,
  194,  95,175,207,
  206, 110,184,230,
  213, 173,203,242,
  218, 206,213,242,
  218,  33, 53, 14,
  219,  44, 62, 14,
  219,  46, 62, 14,
  221,  58, 68, 18,
  223,  75, 73, 24,
  225,  95, 79, 27,
  228, 110, 91, 27,
  230, 126, 97, 31,
  233, 144,111, 27,
  235, 163,118, 27,
  237, 184,125, 26,
  237, 184,125, 27,
  240, 206,141, 25,
  242, 229,149, 25,
  245, 242,166, 24,
  255, 242,223,197};



CRGBPalette16 currentPalette(rainbow_sunset_gp);
CRGBPalette16 targetPalette(rainbow_sunset_gp);

void onPaletteChange() {
  switch (palette) {
      case 0:
        targetPalette = serendil_gp;
        break;
      case 1:
        targetPalette = yule_ribbons_gp;
        break;
      case 2:
        targetPalette = dragon_foot_gp;
        break;
      case 3:
        targetPalette = rainbow_sunset_gp;
        break;
      case 4:
        targetPalette = carousel_gp;
        break;
      case 5:
        targetPalette = Caribbean_gp;
        break;
        
      default:
        targetPalette = rainbow_sunset_gp;
    }
  // Do something
}




void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);

  FastLED.addLeds<WS2811, PIN1, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(intensity);
  FastLED.setDither(0);
  onPaletteChange();
}



void doLeds() {
 
  for (int i = 0; i < NUM_LEDS; i++) {
    uint8_t brightness = inoise8(i * bscale, it);
    uint8_t index = inoise8(i * scale, it);
   
    // scale pallet to full 0-255 range since inoise8 returns roughly 16-238.
    index = qsub8(index,16);
    index = qadd8(index,scale8(index,39));

    // shift leds when changing palette
    leds[(i + paletteChangeTimer) % NUM_LEDS] = ColorFromPalette(currentPalette, index, brightness);
  }
  FastLED.show();
}

void loop() {

    // handle pallet switching
  nblendPaletteTowardPalette( currentPalette, targetPalette, 48 );

  // time axis for 2d noise plot
  t =   (float) millis() * lspeed / 1000.0;
  it = (uint16_t) round(t);

  // display pallet as simplex noise :) 
  EVERY_N_SECONDS(5) {
    doLeds();
  }

  // fast pallet display when changing
  EVERY_N_MILLISECONDS(30) {
    if(paletteChangeTimer) doLeds();
  }

 // decrement pallet change timer
  EVERY_N_SECONDS(1) {
    if(paletteChangeTimer>0) paletteChangeTimer --;
  }


  // toggle adjusting pallet or intensity
  if( rotary.push()) 
    paletteChangeTimer = PALETTE_CHANGE_TIME;
  
  // user interface code
  int r = rotary.rotate();

  // cw
  if (r == 1) 
    if(paletteChangeTimer) {
      palette++;
      paletteChangeTimer = PALETTE_CHANGE_TIME;
    } else {
      intensity+=5;
    }
  

  // ccw
  if (r == 2)
    if(paletteChangeTimer) {
      palette--;
      paletteChangeTimer = PALETTE_CHANGE_TIME;
    } else {
      intensity-=5;
    }
  
  if( r ) {
      if(palette > NUM_PALETTES-1) palette = NUM_PALETTES-1;
      if(palette < 0) palette = 0;
      if(intensity > 255) intensity = 255;
      if(intensity <0) intensity = 0;
      FastLED.setBrightness(intensity);
      onPaletteChange();
      doLeds();
      Serial.print(palette);
      Serial.print(" \t");
      Serial.print(intensity);
      Serial.println();
  }
}
