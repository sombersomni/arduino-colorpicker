# arduino-colorpicker
Uses a nodemcu and arduino to change the color of a rgb LED from a website

## Requirements
* esp8266 nodemcu
* arduino microcontroller
* a rgb led which can control all three color channels

Example for connecting rgb led to arudino
![RGB LED CONNECT](https://www.sunfounder.com/media/wysiwyg/swatches/super-kit-v2-for-Arduino/6_RGB_LED/fes.png)

## Instructions:
1. Take the ardino-slave file and use the Aurdino IDE to upload to your Arduino Uno
2. Take the esp-master file and use the Aurdino IDE to upload it to your NodeMCU module
3. Connect arduino and nodemcu for Wire transfer using 12C. D1(nodemcu) to A4(arduino) &  D2(nodemcu) to A5(arduino)
![12C CONNECT](https://www.electronicwings.com/public/images/user_images/images/NodeMCU/NodeMCU%20Basics%20using%20Arduino%20IDE/NodeMCU%20I2C/Arduino_NodeMCU_I2C_Interface.png)
4. Plug arudino into power source and enjoy!
