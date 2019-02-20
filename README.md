# arduino-colorpicker
Uses a nodemcu and arduino to change the color of a rgb LED from a website

## Requirments
* esp8266 nodemcu
* arduino microcontroller
* a rgb led which can control all three color channels

Example for connecting rgb led to arudino
![GitHub Logo](https://www.sunfounder.com/media/wysiwyg/swatches/super-kit-v2-for-Arduino/6_RGB_LED/fes.png)

## Instructions:
1. Take the ardino-slave file and use the Aurdino IDE to upload to your Arduino Uno
2. Take the esp-master file and use the Aurdino IDE to upload it to your NodeMCU module
3. Connect arduino and nodemcu for Wire transfer. D1(nodemcu) to A4(arduino) &  D2(nodemcu) to A5(arduino)
