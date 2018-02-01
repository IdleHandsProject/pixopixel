// Adafruit_DotStarMatrix example for single DotStar LED matrix.
// Scrolls 'Adafruit' across the matrix.

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_DotStarMatrix.h>
#include <Adafruit_DotStar.h>
#include <Fonts/TomThumb.h>
#include "image.h"

#define DATAPIN    19
#define CLOCKPIN   18


#define SHIFTDELAY 100
#define BRIGHTNESS 50

// MATRIX DECLARATION:
// Parameter 1 = width of DotStar matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   DS_MATRIX_TOP, DS_MATRIX_BOTTOM, DS_MATRIX_LEFT, DS_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     DS_MATRIX_TOP + DS_MATRIX_LEFT for the top-left corner.
//   DS_MATRIX_ROWS, DS_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   DS_MATRIX_PROGRESSIVE, DS_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type:
//   DOTSTAR_BRG  Pixels are wired for BRG bitstream (most DotStar items)
//   DOTSTAR_GBR  Pixels are wired for GBR bitstream (some older DotStars)
//   DOTSTAR_BGR  Pixels are wired for BGR bitstream (APA102-2020 DotStars)

Adafruit_DotStarMatrix matrix = Adafruit_DotStarMatrix(
                                  16, 16, DATAPIN, CLOCKPIN,
                                  DS_MATRIX_BOTTOM     + DS_MATRIX_LEFT +
                                  DS_MATRIX_ROWS + DS_MATRIX_PROGRESSIVE,
                                  DOTSTAR_BGR);

const uint16_t primaryColors[] = {
  matrix.Color(100, 0, 0), matrix.Color(0, 100, 0), matrix.Color(0, 0, 100)
};

const uint16_t adaColors[] = {
  matrix.Color(255, 0, 0),   //A red
  matrix.Color(255, 125, 0), //D orange
  matrix.Color(200, 255, 0), //A yellowish
  matrix.Color(0, 255, 0),   //F green
  matrix.Color(0, 255, 225), //R blue
  matrix.Color(150, 0, 255), //U purple
  matrix.Color(255, 0, 220), //I pink
  matrix.Color(255, 65, 0),  //T reddish
  matrix.Color(255, 220, 0)  //! orange/yellow
};

char adafruit[] = "ADAFRUIT!";

void setup() {
  Serial.begin(115200);

  // uncomment to have wait
  //while (!Serial) delay(500);
  
  matrix.begin();
  
  for (byte i = 0; i < 3; i++) {
    matrix.fillScreen(primaryColors[i]);
    matrix.show();
    delay(500);
    matrix.fillScreen(0);
    matrix.show();
  }
}

int x = matrix.width();
int pass = 0;

void loop() {
  matrix.setBrightness(BRIGHTNESS);
  while(1){
  //  pongDemo();
    SinglePix();
  //  RandomPix();
  //}
  //notification();
  
  }

void SinglePix(){
  for (int x = 0; x<256;x++){
    
    matrix.setPixelColor(x, 255, 255, 255);
    delay(10);
    matrix.show();
    delay(200);
}
}

void RandomPix(){
  randomSeed(A1);
    int x = random(0,256);
    matrix.fillScreen(0);
    matrix.setPixelColor(x, 255, 255, 255);
    matrix.show();
    delay(50);

}

void notification(){
  for (int j = 15; j>=0;j--){
    matrix.fillScreen(0);
    for (int i = 0; i<256; i++) {
    matrix.setPixelColor(i+(j*16), upvote[i][0], upvote[i][1], upvote[i][2]);
    //Serial.println(i);
    //delay(1);
  }
  matrix.show();
  delay(15);
  }
  delay(1000);
  for (int j = 0; j>=-16;j--){
    matrix.fillScreen(0);
    for (int i = 0; i<256; i++) {
    matrix.setPixelColor(i+(j*16), upvote[i][0], upvote[i][1], upvote[i][2]);
    //Serial.println(i);
    //delay(1);
  }
  matrix.show();
  delay(15);
  }
  delay(1000);
  matrix.fillScreen(0);
  matrix.show();
}

float ballx = 5; 
float bally = 5;
float paddle1, paddle2 = 3;
float ballvx = -0.3;
float ballvy = 0.1;

void pongDemo(){
  matrix.fillScreen(0);
  matrix.drawFastVLine(0, (int)paddle1, 6, (200,200,200));
  matrix.drawFastVLine(15, (int)paddle2, 6, (200,200,200));
  matrix.drawPixel((int)ballx,(int)bally,(200,200,200));
  if (ballx > 14 || ballx<1){
    ballvx = ballvx *-1;
  }
  if (bally > 14 || bally<0){
    ballvy = ballvy * -1;
  }
  paddle1 = bally-3;
  paddle2 = bally-3;
  ballx = ballx + ballvx;
  bally = bally + ballvy;
  Serial.print(ballx);
  Serial.print(",");
  Serial.println(bally);
  matrix.show();
  delay(30);
}

