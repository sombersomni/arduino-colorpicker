#include <Wire.h>
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
const int[3] colorPins= {redPin, greenPin, bluePin};
void setup() {
  // put your setup code here, to run once:
  Wire.begin(8);
  Wire.onReceive(changeColor);
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

int i = 0;
void loop() {
  // put your main code here, to run repeatedly:
  //analogWrite(greenPin, i);
  //i = i < 255 ? i + 5 : 0;
}

void changeColor(int howMany) {
  int i = 0;
  while (Wire.available() > 0) {
    int n = Wire.read();
    Serial.print("at pin : ");
    Serial.println(colorPins[i]);
    Serial.print("set color to : ");
    Serial.println(n);
    analogWrite(colorPins[i], n);
    i++;
  }
  Serial.println();
}
