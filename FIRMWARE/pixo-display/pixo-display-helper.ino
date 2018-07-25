/*
 * This is a "Library" of sorts, where I have made several (admittedly basic)
 * functions based off of the original examples provided. Currently these are aimed at
 * displaying what I'll dub "Pixols", the 2D array that contains the pixels and RGB
 * values resulting from using the python image converter.
 * 
 * You can flash this directly to your pixel to see a demonstration of each 
 * 
 * Note that this does not interact with the MPU 
 */

#include <Wire.h>            // For I2C communication
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_DotStarMatrix.h>
#include <Adafruit_DotStar.h>
#include <ArduinoJson.h>
#include "pixols.h"

uint32_t        prevTime = 0;

#define DATAPIN    19
#define CLOCKPIN   18
#define BRIGHTNESS 15
#define TOTALPXLS  256 // The total number of LEDs

// This structure stores the state of all of the LEDS
// The loop will reset various parts of this, such as the active state
// to allow multiple animations to occurr in a row
struct PXL {
    byte id: 1;
    byte r: 1;
    byte g: 1;
    byte b: 1;
    byte active: 1;
};

struct PXL pixols[TOTALPXLS];

Adafruit_DotStarMatrix matrix = Adafruit_DotStarMatrix(
    16, 16, DATAPIN, CLOCKPIN,
    DS_MATRIX_TOP  + DS_MATRIX_LEFT +
    DS_MATRIX_ROWS + DS_MATRIX_PROGRESSIVE,
    DOTSTAR_BGR);

int activePixelCount() {
    int totalActive = 0;
    for (int cnt = 0; cnt < TOTALPXLS; cnt++) {
        if (pixols[cnt].active == true) totalActive++;
    }
    return totalActive;
}

// Use this at the beginning of functions that set the active state
void resetActiveState() {
    for (int i = 0; i < TOTALPXLS; i++) 
        pixols[i].active = false;
}

/*
 * showPxl, displays a Pixol to the display with no animation
 * args:
 * - pxl[TOTALPXLS][3] - Standard Pixol image
 * - dlytime - The amount of time (in ms) to keep the image on the display
 */
void showPxl(int pxl[256][3], int dlytime) {
    matrix.fillScreen(0);

    for (int i=0; i<256; i++){
        matrix.setPixelColor(i, pxl[i][0], pxl[i][1], pxl[i][2]);
    }

    matrix.show();
    delay(dlytime);
  
    matrix.fillScreen(0);
    matrix.show();
}

// Notification functions

/*
 * notifyPopupPxl, draws a Pixol that scrolls into view, and back down
 * args:
 * - pxl[TOTALPXLS][3] - Standard Pixol image
 * - dlytime - The amount of time (in ms) to keep the image on the display
 */
void notifyPopupPxl(int pxl[TOTALPXLS][3], int dlytime) {
    for (int j = 15; j >= 0; j--) {
        for (int i = 0; i < TOTALPXLS; i++) {
            matrix.setPixelColor(i + (j * 16),
                pxl[i][0], pxl[i][1], pxl[i][2]);
        }
        matrix.show();
        delay(50);
    }

    delay(dlytime);

    for (int j = 0; j <= 16; j++) {
        for (int i = 0; i < TOTALPXLS; i++) {
            matrix.setPixelColor(i + (j * 16),
                pxl[i][0], pxl[i][1], pxl[i][2]);
        }
        matrix.show();
        delay(50);
    }

    delay(100);
}

/*
 * notifyScrollPxl, draws a Pixol that scrolls upward into view, and upwards out; Loop this to scroll X times
 * args:
 * - pxl[TOTALPXLS][3] - Standard Pixol image
 * - dlytime - The amount of time (in ms) to keep the image on the display
 * - loops (optional) - The total amount of times this should loop through
 */
void notifyScrollPxl(int pxl[TOTALPXLS][3], int dlytime, int loops=0) {
    for (int x=0; x<=loops; x++) {
        for (int j = 15; j >= 0; j--) {
            for (int i = 0; i < TOTALPXLS; i++) {
                matrix.setPixelColor(i + (j * 16), 
                    pxl[i][0], pxl[i][1], pxl[i][2]);
            }
            matrix.show();
            delay(15);
        }

        delay(dlytime);

        for (int j = 0; j >= -16; j--) {
            for (int i = 0; i < TOTALPXLS; i++) {
                matrix.setPixelColor(i + (j * 16),
                    pxl[i][0], pxl[i][1], pxl[i][2]);
            }
            matrix.show();
            delay(15);
        }

        delay(100);
    }
}

// "Animation" or picture transition functions

/*
 * scanChangePxl, Change from one Pixol to another with a scanline appearence
 * args:
 * - src[TOTALPXLS][3] - Standard Pixo-Style icon that we change from, displayed all at once
 * - dst[TOTALPXLS][3] - Standard Pixo-Style icon that we change to, displayed one pixel at a time
 * - dlytime - The amount of time (in ms) to keep the image on the display
 * - anitime - The amount of time (in ms) between drawing each pixel during the transition; the lower this number, the faster the transition
 */
void scanChangePxl(int src[TOTALPXLS][3], int dst[TOTALPXLS][3], int dlytime, int anitime) {
    for (int i=0; i<TOTALPXLS; i++){
        matrix.setPixelColor(i, src[i][0], src[i][1], src[i][2]);
    }
    matrix.show();

    delay(dlytime);

    for (int i=0; i<TOTALPXLS; i++){
        matrix.setPixelColor(i, dst[i][0], dst[i][1], dst[i][2]);
        matrix.show();
        delay(anitime);
    }

    delay(dlytime);
}

/*
 * randChangePxl, Change from one Pixol to another with a random pixel selection
 * args:
 * - src[TOTALPXLS][3] - Standard Pixo-Style icon that we change from, displayed all at once
 * - dst[TOTALPXLS][3] - Standard Pixo-Style icon that we change to, displayed one pixel at a time
 * - dlytime - The amount of time (in ms) to keep the image on the display
 * - anitime - The amount of time (in ms) between drawing each pixel during the transition; the lower this number, the faster the transition
 */
void randChangePxl(int src[256][3], int dst[256][3], int dlytime, int anitime) {
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

    showPxl(twitter, 1000);
    notifyPopupPxl(glogo, 500);
    notifyScrollPxl(upvote, 1000, 4);
    notifyScrollPxl(mario, 1000); // Not specifying the loop will make it only show once

    // This is supposed to be a random pixel fill transition, but 
    // the rng does not guarentee unique numbers in the range automatically
    randChangePxl(mario, pridec0de, 1000, 10);
}