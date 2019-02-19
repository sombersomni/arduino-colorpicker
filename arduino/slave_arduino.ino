#include <Wire.h>
const int bluePin = 9;
const int redPin = 10;
const int greenPin = 11;
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
  char arr[6];
  while (Wire.available() > 0) {
    char c = Wire.read();
    Serial.print(c);
  }
  Serial.println();
}
