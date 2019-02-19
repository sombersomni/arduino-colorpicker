#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>
#include <Wire.h>
#include <cstdlib>
#include <string>

ESP8266WiFiMulti WiFiMulti;
String url = "http://nameless-fortress-94924.herokuapp.com/getcolor";
String prevPayload = "";
void setup() {

  // Serial.setDebugOutput(true);
  // join i2c bus with SDA=D1 and SCL=D2 of NodeMCU
  Wire.begin(D1, D2);
  Serial.begin(9600);
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("2WIRE744", "1378814274");

}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    Serial.println(WiFi.localIP());
    if (http.begin(client, url)) {  // HTTP


      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();
      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          if (payload != prevPayload) {
            prevPayload = payload;
            //payload.c_str()
            Serial.println(payload);
            //sends message
            Wire.beginTransmission(8);
            Wire.write(255);
            Wire.write(0);
            Wire.write(0);
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

  delay(10000);
}
