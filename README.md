# The PIXO Pixel
PIXO Pixel is a 16 x 16 RGB LED display that runs off of an ESP32.
This project is open source!
You can find the Bill of Materials [here](https://www.findchips.com/org/10-open-hardware/list/85998-pixo-pixel-esp-board-and-led-board) on FindChips.

I have submitted a pull request to the Arduino-ESP32 github: https://github.com/espressif/arduino-esp32 to have the PIXO Pixel have its own board file. This will ensure the pinout that was used will match the pin declartion on the board. In the meantime, please use the "Adafruit Feather ESP32" in the board manager, as the pinout is the same.

## Flashing Firmware Instructions
1. You need to have the current version of the [Arduino IDE](https://arduino.cc) installed
2. Ensure that you have the [Arduino ESP32 Boards](https://github.com/espressif/arduino-esp32) installed (This library is currently broken, a workaround has been found [Here](https://github.com/espressif/arduino-esp32/issues/1559))
3. Various other libraries are required for the example firmware; they are listed below under "Libraries used in Example Firmware"
4. Connect your pixo pixel to your computer and start Arduino
5. Under the "Tools" menu, select "Board->Adafruit ESP32 Feather"; Leave Flash frequency and Upload speed the default
6. Under Port, select your pixo
7. Compile and upload
8. When the Arduino console says "Connecting....", press and release both the boot and reset buttons simultaniously
9. You should start to see output about flashing
10. When the flash is complete, press the reset button on the pixo to start your new firmware

[Here](https://youtu.be/dVT4Nei8qHg) is a video of Sean going into detail demonstrating some of the examples

## Libraries used in Example Firmware
Install these to your sketchbook's `libraries` folder, usually located in `YOUR HOME/Documents/Arduino`

* [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library)
* [Adafruit DotStar](https://github.com/adafruit/Adafruit_DotStar)
* [Adafruit DotStar Matrix](https://github.com/adafruit/Adafruit_DotStarMatrix)
* [ArduinoJson](https://github.com/bblanchon/ArduinoJson)
* [i2cdevlib](https://github.com/jrowberg/i2cdevlib)

**Note** Arduino IDE was complaining about i2cdevlib being invalid as the installation instructions are a bit unclear.
It seems that the ESP32 is not officially supported for use with these libraries, and I had to apply a patch ([#367](https://github.com/jrowberg/i2cdevlib/pull/367)) to get no compile errors.

### Patching I2Cdev and MPU6050 Libraries
1. Download i2cdevlib and extract the zip file
2. Inside the i2cdevlib/Arduino, copy `I2Cdev` and `MPU6050` folders to your `libraries` folder
3. Edit `I2Cdev/I2Cdev.cpp`, and immedietly under `#include "I2Cdev.h"`, add the following
```
#ifdef ARDUINO_ARCH_ESP32
#define BUFFER_LENGTH I2C_BUFFER_LENGTH
#endif
```
4. Edit `MPU6050/MPU6050_6Axis_MotionApps20.h` and add the following right above the `DEBUG` section
```
#ifndef ARDUINO_ARCH_ESP32
    typedef void prog_void;
    typedef char prog_char;
    typedef unsigned char prog_uchar;
    typedef int8_t prog_int8_t;
    typedef uint8_t prog_uint8_t;
    typedef int16_t prog_int16_t;
    typedef uint16_t prog_uint16_t;
    typedef int32_t prog_int32_t;
    typedef uint32_t prog_uint32_t;
#endif
```
5. Restart Arduino

There's a whole bunch of other commits in here, but this seems mostly to be a mix of: feature adding, bug fixing, and various other changes that may or may not be related. Feel free to experiment with these at your own discretion.

## Kickstarter - Success
This was a [Make100 Kickstarter](https://www.kickstarter.com/projects/idlehandsdev/pixo-pixel-an-esp32-based-iot-rgb-display-for-make) that was recently fulfilled

[![Kickstarter Vid](https://img.youtube.com/vi/XT5R4Tftu7k/0.jpg)](https://youtu.be/XT5R4Tftu7k)

[Completion Video](https://youtu.be/YA3uAYVbMNc)