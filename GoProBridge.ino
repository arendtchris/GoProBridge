#include "GoProCamera.h"
#include "StatusDecoder.h"
#include "CommandParser.h"
#include "config.h"
#include <WiFi.h>

StatusDecoder decoder;
CommandParser parser;

HardwareSerial fcSerial(0);        // UART0 ESP32-C3
const int baudRate = 115200;
unsigned long lastUpdate = 0;
String input = "";
GoProCamera camera( "http://10.5.5.9:8080");



void setup() {
  Serial.begin(115200);
  fcSerial.begin(baudRate, SERIAL_8N1, 20, 21);
  delay(1000);
  WiFi.useStaticBuffers(true);
  WiFi.mode(WIFI_STA);
  WiFi.setTxPower(WIFI_POWER_8_5dBm);
}

void loop() {


  if (millis() - lastUpdate > 1000) {

    lastUpdate = millis();

    if (WiFi.status() != WL_CONNECTED)
    {
      //Serial.println("Camera offline");
      String json  = R"JSON({"status":{"1":0}})JSON";

    } else {
      String json = camera.update();
      fcSerial.println(json);
    }


  }

  if (fcSerial.available()) {
    String cmd = fcSerial.readStringUntil('\n');
    Serial.println(cmd);
    parser.handle( camera, cmd);
  }


}
