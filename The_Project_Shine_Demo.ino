#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_Circuit_Playground.h>


// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls 'Howdy' across the matrix in a portrait (vertical) orientation.

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

#define PIN 6
int i = 0;

float value;


// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)


// Example for NeoPixel Shield.  In this application we'd like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino.  When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order.  The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(16, 16, PIN,
                            NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB            + NEO_KHZ800);
const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)
};

void setup() {
  CircuitPlayground.begin();
  matrix.begin();
  matrix.setBrightness(40);
  Serial.begin(9600);
}
int x    = matrix.width();
int pass = 0;

void loop() {
  if (CircuitPlayground.rightButton()) {
    i++;
    if (i > 3) i = 0;
  }
  Serial.println(i);
  if (i == 0) {
    matrix.fillScreen(0);
  }
  if (i == 1) {
    scrollingText();
  }
  else if (i == 2) {
    soundReactive();
  }
  else if (i == 3) {
    appleLogo();
  }
  delay(100);
}


void scrollingText() {  //function for scrolling text
  matrix.fillScreen(0);
  matrix.setCursor(x, 4 );
  matrix.print(F("Ariv"));
  if (--x < -60) {
    x = matrix.width();
    if (++pass >= 3) pass = 0;
    matrix.setTextColor(colors[pass]);
  }
  matrix.show();
}
void soundReactive() {  //function for sound reactive
  value = CircuitPlayground.mic.soundPressureLevel(10) - 58;//minus by base level of sound
  //Serial.println(value);
  float sound = value * (16.0 / 42.0); //minus by level left
  int wave = 16 - sound;
  for (int i = 16; i > wave; i--) {
    matrix.drawLine(0, i, 16, i, matrix.Color(0, 0, 255));
  }
  matrix.show();
  //matrix.fillScreen(matrix.Color(0, 0, 0));
}

void appleLogo() {  //function for apple logo
  int doubleArray[16][16] =
  { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 3, 4, 4, 5, 5, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 3, 3, 4, 4, 5, 5, 6, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 3, 3, 4, 4, 5, 5, 6, 6, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 3, 4, 4, 5, 5, 6, 6, 0, 0, 0, 0},
    {0, 0, 2, 2, 0, 3, 4, 4, 5, 5, 6, 6, 0, 0, 0, 0},
    {0, 1, 1, 2, 0, 3, 4, 4, 5, 5, 6, 6, 0, 0, 0, 0},
    {0, 1, 1, 0, 3, 3, 4, 4, 5, 5, 6, 6, 0, 0, 0, 0},
    {0, 0, 0, 0, 3, 3, 4, 4, 5, 5, 6, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 3, 4, 0, 0, 5, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
      if (doubleArray[j][i] == 1) {
        matrix.drawPixel(j, i, matrix.Color(100, 186, 77));
      }
      if (doubleArray[j][i] == 2) {
        matrix.drawPixel(j, i, matrix.Color(251, 183, 56));
      }
      if (doubleArray[j][i] == 3) {
        matrix.drawPixel(j, i, matrix.Color(243, 131, 45));
      }
      if (doubleArray[j][i] == 4) {
        matrix.drawPixel(j, i, matrix.Color(222, 57, 64));
      }
      if (doubleArray[j][i] == 5) {
        matrix.drawPixel(j, i, matrix.Color(150, 60, 151));
      }
      if (doubleArray[j][i] == 6) {
        matrix.drawPixel(j, i, matrix.Color(26, 161, 219));
      }
    }
  }
  matrix.show();
}
