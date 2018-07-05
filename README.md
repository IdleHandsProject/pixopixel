# The PIXO Pixel
PIXO Pixel is a 16 x 16 RGB LED display that runs off of an ESP32.

I have submitted a pull request to the Arduino-ESP32 github: https://github.com/espressif/arduino-esp32 to have the PIXO Pixel have its own board file. This will ensure the pinout that was used will match the pin declartion on the board. In the meantime, please use the "Adafruit Feather ESP32" in the board manager, as the pinout is the same.

Find the BOM on FindChips here: https://www.findchips.com/org/10-open-hardware/list/85998-pixo-pixel-esp-board-and-led-board

It is currently a Kickstarter! Go check it out here:
https://www.kickstarter.com/projects/idlehandsdev/pixo-pixel-an-esp32-based-iot-rgb-display-for-make

[![Kickstarter Vid](https://img.youtube.com/vi/XT5R4Tftu7k/0.jpg)](https://youtu.be/XT5R4Tftu7k)

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

## Libraries used in Example Firmware
Install these to your sketchbook's `libraries` folder, usually located in `YOUR HOME/Documents/Arduino`

* [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library)
* [Adafruit DotStar](https://github.com/adafruit/Adafruit_DotStar)
* [Adafruit DotStar Matrix](https://github.com/adafruit/Adafruit_DotStarMatrix)
* [ArduinoJson](https://github.com/bblanchon/ArduinoJson)
* [i2cdevlib](https://github.com/jrowberg/i2cdevlib)

**Note** Arduino IDE was complaining about i2cdevlib being invalid as the installation instructions are a bit unclear.
I found that copying the `I2Cdev` and `MPU6050` folders to the libraries folder from the Arduino folder seems to *kinda* work.
Perhaps I have the wrong library, because I get compile errors when trying to use either `I2Cdev` or `MPU6050` from the above source.
