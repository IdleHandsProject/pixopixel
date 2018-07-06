#include <Wire.h>            // For I2C communication
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_DotStarMatrix.h>
#include <Adafruit_DotStar.h>
#include <ArduinoJson.h>
#include "image.h"

#define WIDTH        16 // Display width in pixels
#define HEIGHT       16 // Display height in pixels
#define MAX_FPS      45 

#define MAX_X (WIDTH  * SCALE - 1) 
#define MAX_Y (HEIGHT * SCALE - 1) 

uint32_t        prevTime   = 0;      
uint8_t         backbuffer = 0,      
                img[WIDTH * HEIGHT];

#define DATAPIN    19
#define CLOCKPIN   18
#define SHIFTDELAY 30
#define BRIGHTNESS 15

Adafruit_DotStarMatrix matrix = Adafruit_DotStarMatrix(
    16, 16, DATAPIN, CLOCKPIN,
    DS_MATRIX_TOP  + DS_MATRIX_LEFT +
    DS_MATRIX_ROWS + DS_MATRIX_PROGRESSIVE,
    DOTSTAR_BGR);


void setup(void) {
    matrix.begin();
    matrix.setBrightness(BRIGHTNESS);
}

void loop() {
    uint32_t t;
    while (((t = micros()) - prevTime) < (1000000L / MAX_FPS)); // FPS Limit?
    prevTime = t;
}
