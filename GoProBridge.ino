#include "GoProCamera.h"
#include "StatusDecoder.h"
#include "CommandParser.h"
#include "config.h"

GoProCamera camera;
StatusDecoder decoder;
CommandParser parser;

HardwareSerial fcSerial(0);        // UART0 ESP32-C3
const int baudRate = 115200;

unsigned long lastUpdate = 0;
String input = "";
void setup() {
    Serial.begin(115200);
    fcSerial.begin(baudRate, SERIAL_8N1, 20, 21);
    delay(1000);
    camera.begin(WIFI_SSID, WIFI_PASS);
}

void loop() {

    if (millis() - lastUpdate > 1000) {
        lastUpdate = millis();
        //Serial.println(camera.keepAlive());
        Serial.println(camera.wifiStatus());
        Serial.println(camera.update());
        
        fcSerial.println(camera.update());
    }

    if (fcSerial.available()) {
        String cmd = fcSerial.readStringUntil('\n');
       // parser.handle( camera, cmd);
    }

   if (Serial.available()) {
        String cmd = Serial.readStringUntil('\n');
       parser.handle( camera, cmd);
    }
}
