/*
  Accerlerometer Pong for the PIXO Pixel.
  Utilizes the Adafruit GFX Libraries as well as the DotStar Libraries.

  This version is created to use with the MPU6050

  Developed by Sean Hodgins and is licensed under GPL 3.0
*/

#include <Wire.h>            // For I2C communication
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_DotStarMatrix.h>
#include <Adafruit_DotStar.h>
#include <ArduinoJson.h>
#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 mpu;

#define WIDTH        16 // Display width in pixels
#define HEIGHT       16 // Display height in pixels
#define MAX_FPS      45 // Maximum redraw rate, frames/second
#define SCALE        128


int ballx = 5 * SCALE;
int bally = 5 * SCALE;
int ballvx = 20;
int ballvy = 10;
int p1 = 6;
int p2 = 6;
int PW = 5;
int lasty = 0;
int curry = 0;
int p2a = 1;
int p2v = 0;
int p2loc = 256;
int p1score = 0;
int p2score = 0;
int difficulty = 0;

uint32_t prevTime = 0;

int16_t rax, ray, raz;
int16_t rgx, rgy, rgz;

#define DATAPIN    19
#define CLOCKPIN   18

#define BRIGHTNESS 30

Adafruit_DotStarMatrix pixo = Adafruit_DotStarMatrix(
                                16, 16, DATAPIN, CLOCKPIN,
                                DS_MATRIX_TOP    + DS_MATRIX_LEFT +
                                DS_MATRIX_ROWS + DS_MATRIX_PROGRESSIVE,
                                DOTSTAR_BGR);


void setup(void) {
  uint8_t i, j, bytes;
  Serial.begin(115200);

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif
  Serial.println("Initializing I2C devices...");
  mpu.initialize();

  Serial.println("Testing device connections...");
  Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  pixo.begin();

  pixo.setBrightness(BRIGHTNESS);
}


void loop() {



  uint32_t t;
  while (((t = micros()) - prevTime) < (1000000L / MAX_FPS));
  prevTime = t;



  // Read accelerometer...
  mpu.getMotion6(&rax, &ray, &raz, &rgx, &rgy, &rgz);
  randomSeed(A7);

  ballx = ballx + ballvx; //Move Ball
  bally = bally + ballvy;

  curry = (0.90 * lasty) + (0.1 * ray); //Filter Accelerometer data for user paddle
  lasty = curry;


  p1 = map(curry, -4000, 4000, 0, (16 - PW) * SCALE);
  int  p1s = p1 / SCALE;
  p1s = constrain(p1s, 1, 16 - PW);

  p2v = constrain(p2v, -25, 25);
  p2loc = p2loc + p2v;
  p2 = p2loc / SCALE;
  p2 = constrain(p2, 1, 16 - PW);

  int bys = bally / SCALE;

  if (ballx > (14 * SCALE)) {
    if (bys >= p2 && bys <= (p2 + PW)) {
      ballvx = (ballvx) * -1.1;
      ballvx = constrain(ballvx, -40, 40);
      difficulty++;
      paddleDeflect(p2loc, bally, PW);
    }
    if (ballx > (15 * SCALE) + 50) {
      if (bys < p2 || bys > (p2 + PW)) {
        delay(2000);
        p1score++;

        resetGame();
      }
    }
  }
  if (ballx < SCALE) {
    if (bys >= p1s && bys <= (p1s + PW)) {
      ballvx = (ballvx ) * -1.1;
      ballvx = constrain(ballvx, -40, 40);
      difficulty++;
      paddleDeflect(p1, bally, PW);

    }
    if (ballx < 10) {
      if (bys < p1s || bys > (p1s + PW)) {
        delay(2000);
        p2score++;

        resetGame();

      }
    }
  }
  if (bally > (15 * SCALE) || bally < SCALE + 10) {
    ballvy = ballvy * -1;
  }

  if ((p2loc + ((PW / 2) * SCALE)) < bally) {
    p2v = p2v + p2a;
  }
  if ((p2loc + ((PW / 2) * SCALE)) > bally) {
    p2v = p2v - p2a;

  }
  //SEND TO DISPLAY
  pixo.fillScreen(0);
  pixo.drawFastHLine(0, 0, 16, pixo.Color(100, 0, 0));
  pixo.drawFastHLine(5, 0, 6, pixo.Color(100, 100, 0));
  if (p2score > 0) {
    pixo.drawFastHLine(17, 0, -p2score, pixo.Color(0, 200, 0));
  }
  if (p1score > 0) {
    pixo.drawFastHLine(0, 0, p1score, pixo.Color(0, 200, 0));
  }
  pixo.drawFastVLine(0, p1s, PW, pixo.Color(200, 255, 255));
  pixo.drawFastVLine(15, p2, PW, pixo.Color(200, 255, 255));
  pixo.drawPixel((ballx / SCALE), (bally / SCALE), pixo.Color(200, 255, 255));
  pixo.show();

  //GAME HAS ENDED
  if (p1score == 5 || p2score == 5) {
    while (1);
  }
}



void paddleDeflect(int ploc, int bloc, int pwidth) {
  int err = bloc - (ploc + (pwidth * SCALE) / 2);
  int diff = difficulty / 2;
  //Serial.println(diff);
  err = map(err, -300, 300, -10 - diff, 10 + diff);
  err = constrain(err, -25, 25);
  ballvy = err;
}

void resetGame() {
  ballx = 5 * SCALE;
  bally = 5 * SCALE;
  ballvx = 20;
  ballvy = 10;
  p1 = 6;
  p2 = 6;
  p2a = 1;
  p2v = 0;
  p2loc = 256;
}

