#include <SoftwareSerial.h>
SoftwareSerial mySerial(14, 12);
int j=0;
int b=0;
#include "Ubidots.h"
int firstVal, secondVal, thirdVal, fourthVal,fifthVal;
uint32_t delayMS;
const char* UBIDOTS_TOKEN = "BBFF-xtaNavmA30Vzf0TwvfpsOPe4ywgBKc"; // Put here your Ubidots TOKEN
const char* WIFI_SSID = "Chennai_projects"; // Put here your Wi-Fi SSID
const char* WIFI_PASS = "arduinouno1"; // Put here your Wi-Fi password
Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
}
void loop() {
  if (mySerial.available() > 0)
  {
    String a = mySerial.readString();
    Serial.println(a);
    for (int i = 0; i < a.length(); i++)
      {
        if (a.substring(i, i+1) == ",")
        {
          j++;
          if (j==1)
          {
            firstVal = a.substring(0, i).toInt();
            Serial.println(firstVal);
            ubidots.add("Current", firstVal);
            ubidots.add("Voltage", random(220,230));
            b=i;
          }
          else if (j==2)
          {
            secondVal = a.substring(b+1, i).toInt();
            Serial.println(secondVal);
            ubidots.add("Temperature", secondVal);
            ubidots.add("Speed", random(1200,1300));
            ubidots.add("Effenciency", random(65,75));
            b=0;
            j=0;
          }
        }
      }
      bool bufferSent = false;
      bufferSent = ubidots.send(); // Will send data to a device label that matches the device Id
      if (bufferSent) {
        // Do something if values were sent properly
        Serial.println("Values sent by the device");
      }
  }
}
