//--------------------------------------------------------------------------
// This code is modified from the following Adafruit tutorial: https://learn.adafruit.com/animated-led-sand/overview
/*

    This code is modified from the following Adafruit tutorial: https://learn.adafruit.com/animated-led-sand/overview
    This program shows an upvote arrow 3 times then on the 4th it breaks into particles that will move based on accelerometer readings.
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

uint8_t upvote[256][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 68, 0}, {255, 68, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {0, 0, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {255, 68, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
int sh[256][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {1, 1, 1}, {2, 2, 2}, {3, 3, 3}, {3, 3, 3}, {2, 2, 2}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {3, 3, 3}, {3, 3, 3}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {22, 22, 22}, {58, 58, 58}, {78, 78, 78}, {86, 86, 86}, {69, 69, 69}, {5, 5, 5}, {1, 1, 1}, {3, 3, 3}, {0, 0, 0}, {2, 2, 2}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {86, 86, 86}, {154, 154, 154}, {114, 114, 114}, {73, 73, 73}, {49, 49, 49}, {40, 40, 40}, {39, 39, 39}, {6, 6, 6}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {93, 93, 93}, {163, 163, 163}, {118, 118, 118}, {65, 65, 65}, {17, 17, 17}, {0, 0, 0}, {0, 0, 0}, {1, 1, 1}, {14, 14, 14}, {52, 52, 52}, {0, 0, 0}, {35, 35, 35}, {0, 0, 0}, {2, 2, 2}, {3, 3, 3}, {2, 2, 2}, {0, 0, 0}, {0, 0, 0}, {30, 30, 30}, {74, 74, 74}, {114, 114, 114}, {122, 122, 122}, {54, 54, 54}, {0, 0, 0}, {21, 21, 21}, {211, 211, 211}, {4, 4, 4}, {174, 174, 174}, {48, 48, 48}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {3, 3, 3}, {2, 2, 2}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {32, 32, 32}, {131, 131, 131}, {108, 108, 108}, {0, 0, 0}, {183, 183, 183}, {38, 38, 38}, {136, 136, 136}, {130, 130, 130}, {41, 41, 41}, {75, 75, 75}, {78, 78, 78}, {0, 0, 0}, {0, 0, 0}, {2, 2, 2}, {0, 0, 0}, {0, 0, 0}, {20, 20, 20}, {51, 51, 51}, {199, 199, 199}, {152, 152, 152}, {199, 199, 199}, {116, 116, 116}, {110, 110, 110}, {193, 193, 193}, {51, 51, 51}, {46, 46, 46}, {25, 25, 25}, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, {61, 61, 61}, {154, 154, 154}, {123, 123, 123}, {76, 76, 76}, {53, 53, 53}, {173, 173, 173}, {155, 155, 155}, {123, 123, 123}, {0, 0, 0}, {181, 181, 181}, {4, 4, 4}, {0, 0, 0}, {0, 0, 0}, {2, 2, 2}, {0, 0, 0}, {49, 49, 49}, {209, 209, 209}, {32, 32, 32}, {0, 0, 0}, {0, 0, 0}, {117, 117, 117}, {126, 126, 126}, {53, 53, 53}, {135, 135, 135}, {1, 1, 1}, {134, 134, 134}, {63, 63, 63}, {2, 2, 2}, {3, 3, 3}, {1, 1, 1}, {1, 1, 1}, {24, 24, 24}, {124, 124, 124}, {87, 87, 87}, {75, 75, 75}, {126, 126, 126}, {143, 143, 143}, {11, 11, 11}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {53, 53, 53}, {126, 126, 126}, {0, 0, 0}, {3, 3, 3}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {25, 25, 25}, {35, 35, 35}, {24, 24, 24}, {0, 0, 0}, {0, 0, 0}, {2, 2, 2}, {3, 3, 3}, {0, 0, 0}, {0, 0, 0}, {35, 35, 35}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {1, 1, 1}, {2, 2, 2}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {3, 3, 3}, {1, 1, 1}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {1, 1, 1}, {1, 1, 1}, {1, 1, 1}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

//int N_GRAINS = 0;
#define N_GRAINS     58 // Number of grains of sand
#define WIDTH        16 // Display width in pixels
#define HEIGHT       16 // Display height in pixels
#define MAX_FPS      45 
#define SCALE        128
#define WBOUNCE      -2
#define BBOUNCE      -2

#define MAX_X (WIDTH  * SCALE - 1) 
#define MAX_Y (HEIGHT * SCALE - 1) 
struct Grain {
  int16_t  x,  y; 
  int16_t vx, vy; 
} grain[N_GRAINS];

int16_t rax, ray, raz;
int16_t rgx, rgy, rgz;
uint32_t        prevTime   = 0;      
uint8_t         backbuffer = 0,      
                img[WIDTH * HEIGHT];



#define DATAPIN    19
#define CLOCKPIN   18


#define SHIFTDELAY 30
#define BRIGHTNESS 100



Adafruit_DotStarMatrix matrix = Adafruit_DotStarMatrix(
                                  16, 16, DATAPIN, CLOCKPIN,
                                  DS_MATRIX_TOP    + DS_MATRIX_LEFT +
                                  DS_MATRIX_ROWS + DS_MATRIX_PROGRESSIVE,
                                  DOTSTAR_BGR);


void setup(void) {
  uint8_t i, j, bytes;
  Serial.begin(115200);
  Serial.println("Thanks for Backing the PIXO Pixel!");
  delay(300);
  Serial.println("Go check out the build video on my YouTube!");
  delay(300);
  Serial.println("http://youtube.com/seanhodginsfilms");
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif
  Serial.println("Initializing I2C devices...");
  mpu.initialize();
  Serial.println("Testing device connections...");
  Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  matrix.begin();
  matrix.setBrightness(BRIGHTNESS);

  
//    screenFlash();
//    delay(500);
//    screenFlash();
//    delay(500);
  
//
//  notification();
//  notificationhalf();

  memset(img, 0, sizeof(img)); // Clear the img[] array
  int grain_num = 0;
  for (int x = 0; x < 256; x++) {
    if (sh[x][0] > 50) {

      int NX = x % 16;
      int NY = x / 16;
      grain[grain_num].x = (NX  * SCALE); // Assign random position within
      grain[grain_num].y = (NY * SCALE);
      grain_num++;
    }
  }

  for (i = 0; i < N_GRAINS; i++) { // For each sand grain...
    img[(grain[i].y / SCALE) * WIDTH + (grain[i].x / SCALE)] = 255; // Mark it
    grain[i].vx = grain[i].vy = 0; // Initial velocity is zero
  }
}


void loop() {


  mpu.getMotion6(&rax, &ray, &raz, &rgx, &rgy, &rgz);
  randomSeed(A7);

  int16_t ax = random(-11,11);    // Transform accelerometer axes
  ax = ax / 10;
   int16_t ay = random(-11,11);    // Transform accelerometer axes
  ay = ay / 10;
  matrix.fillScreen(0);
  Serial.println(ax);
    matrix.fillCircle(8-ax, 8-ay, 2, matrix.Color(0, 150, 90));
  matrix.show();
  delay(50);
}


