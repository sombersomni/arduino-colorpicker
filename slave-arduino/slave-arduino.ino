#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>
#include <Wire.h>

ESP8266WiFiMulti WiFiMulti;
//starting values
String url = "http://still-sierra-29382.herokuapp.com/getcolor"; //use an heroku app to test out and use endpoint getcolor for your url
String prevPayload = "";

void getColors (String str, int* colors, char sep);
void setup() {

  // Serial.setDebugOutput(true);
  // join i2c bus with SDA=D1 and SCL=D2 of NodeMCU
  Wire.begin(D1, D2);
  Serial.begin(9600);
  Serial.println();

  Serial.println("Please Wait");
  delay(5000);

  WiFi.mode(WIFI_STA);
  //Use your own SSID and PASSWORD
  WiFiMulti.addAP("SSID", "PASSWORD"); 

}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    Serial.print("Starting client...\n");
    Serial.println(WiFi.localIP());
    if (http.begin(client, url)) {  // HTTP


      Serial.print("[HTTP] GET ");
      Serial.print(url);
      Serial.println();
      // start connection and send HTTP header
      int httpCode = http.GET();
      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("GET code is : %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          if (payload != prevPayload) {
            prevPayload = payload;
            //payload.c_str()
            Serial.println(payload);
            //breaks string int array of numbers
            int colors[3];
            getColors(payload, colors, ',');
            //sends message
            Wire.beginTransmission(8);
            //send each number seperately
            Wire.write(colors[0]);
            Wire.write(colors[1]);
            Wire.write(colors[2]);  
            Wire.endTransmission();
          }
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }

  delay(2000);
}

void getColors (String str, int* colors, char sep = ',') {
  String colorString;
  uint8_t prevPos = 0;
  uint8_t pos = 0;
  short int i = 0;
  while(i < 3) {
    //find position of all commas
    prevPos = pos;
    pos = str.indexOf(sep, pos == 0 ? 0 : pos + 1);
    prevPos += prevPos == 0 ? 0 : 1;
    colorString = str.substring(prevPos, i == 2 ? str.length() : pos);
    Serial.print("getColor running : ");
    Serial.println(colorString);
    colors[i] = colorString.toInt();
    i++;
  }
}
