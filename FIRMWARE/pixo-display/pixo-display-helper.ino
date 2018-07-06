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

    scanChangeImage(darkness, sh, 1000, 10);
}

/*
 * showImage, displays an image to the display with no animation
 * args:
 * - img[256][3] - Standard Pixo-Style icon
 * - dlytime - The amount of time (in ms) to keep the image on the display
 */
void showImage(int img[256][3], int dlytime) {
    matrix.fillScreen(0);

    for (int i=0; i<256; i++){
        matrix.setPixelColor(i, img[i][0], img[i][1], img[i][2]);
    }

    matrix.show();
    delay(dlytime);
  
    matrix.fillScreen(0);
    matrix.show();
}

// Notification functions

/*
 * notifyPopupImg, draws an image that scrolls into view, and back down
 * args:
 * - img[256][3] - Standard Pixo-Style icon
 * - dlytime - The amount of time (in ms) to keep the image on the display
 */
void notifyPopupImg(int img[256][3], int dlytime) {
    for (int j = 15; j >= 0; j--) {
        matrix.fillScreen(0);
        for (int i = 0; i < 256; i++) {
            matrix.setPixelColor(i + (j * 16),
                img[i][0], img[i][1], img[i][2]);
        }
        matrix.show();
        delay(50);
    }

    delay(dlytime);

    for (int j = 0; j <= 16; j++) {
        matrix.fillScreen(0);
        for (int i = 0; i < 256; i++) {
        matrix.setPixelColor(i + (j * 16),
            img[i][0], img[i][1], img[i][2]);
        }
        matrix.show();
        delay(50);
    }

    delay(100);
    matrix.fillScreen(0);
    matrix.show();
}

/*
 * notifyScrollImg, draws an image that scrolls upward into view, and upwards out; Loop this to scroll continuously
 * args:
 * - img[256][3] - Standard Pixo-Style icon
 * - dlytime - The amount of time (in ms) to keep the image on the display
 * - loops (optional) - The total amount of times this should loop through
 */
void notifyScrollImg(int img[256][3], int dlytime, int loops=0) {
    for (int x=0; x<=loops; x++) {
        for (int j = 15; j >= 0; j--) {
            matrix.fillScreen(0);
            for (int i = 0; i < 256; i++) {
                matrix.setPixelColor(i + (j * 16), 
                    img[i][0], img[i][1], img[i][2]);
            }
            matrix.show();
            delay(15);
        }

        delay(dlytime);

        for (int j = 0; j >= -16; j--) {
            matrix.fillScreen(0);
            for (int i = 0; i < 256; i++) {
                matrix.setPixelColor(i + (j * 16),
                    img[i][0], img[i][1], img[i][2]);
            }
            matrix.show();
            delay(15);
        }

        delay(100);
        matrix.fillScreen(0);
        matrix.show();
    }
}

// "Animation" or picture transition functions

/*
 * scanChangeImage, Change from one image to another with a scanline appearence
 * args:
 * - src[256][3] - Standard Pixo-Style icon that we change from, displayed all at once
 * - dst[256][3] - Standard Pixo-Style icon that we change to, displayed one pixel at a time
 * - dlytime - The amount of time (in ms) to keep the image on the display
 * - anitime - The amount of time (in ms) between drawing each pixel during the transition; the lower this number, the faster the transition
 */
void scanChangeImage(int src[256][3], int dst[256][3], int dlytime, int anitime) {
    for (int i=0; i<256; i++){
        matrix.setPixelColor(i, src[i][0], src[i][1], src[i][2]);
    }
    matrix.show();

    delay(dlytime);

    for (int i=0; i<256; i++){
        matrix.setPixelColor(i, dst[i][0], dst[i][1], dst[i][2]);
        matrix.show();
        delay(anitime);
    }

    delay(dlytime);
}

/*
 * randChangeImage, Change from one image to another with a random pixel selection
 * args:
 * - src[256][3] - Standard Pixo-Style icon that we change from, displayed all at once
 * - dst[256][3] - Standard Pixo-Style icon that we change to, displayed one pixel at a time
 * - dlytime - The amount of time (in ms) to keep the image on the display
 * - anitime - The amount of time (in ms) between drawing each pixel during the transition; the lower this number, the faster the transition
 */
void randChangeImage(int src[256][3], int dst[256][3], int dlytime, int anitime) {
    int changed[256];
    for (int i=0; i<256; i++){
        matrix.setPixelColor(i, src[i][0], src[i][1], src[i][2]);
    }
    matrix.show();

    delay(dlytime);

    for (int i=0; i<256; i++){
        int selected = random(0, 256);
        // If the selected pixel was inside changed array, select a new one...
        // Add selected to changed array
        matrix.setPixelColor(selected, dst[selected][0], dst[selected][1], dst[selected][2]);
        matrix.show();
        delay(anitime);
    }

    delay(dlytime);
}

// Loop is at the bottom because Arduino started giving me undefined function errors...
void loop() {
    uint32_t t;
    while (((t = micros()) - prevTime) < (1000000L / MAX_FPS)); // FPS Limit?
    prevTime = t;

    showImage(twitter, 1000);
    notifyPopupImg(glogo, 500);
    notifyScrollImg(upvote, 1000, 4);

    randChangeImage(mario, pridec0de, 1000, 10);
}