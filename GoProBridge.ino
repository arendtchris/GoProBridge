#include "GoProCamera.h"
#include "StatusDecoder.h"
#include "CommandParser.h"
#include "config.h"

GoProCamera camera;
StatusDecoder decoder;
CommandParser parser;

unsigned long lastUpdate = 0;

void setup() {
    Serial.begin(115200);

    camera.begin(WIFI_SSID, WIFI_PASS);
}

void loop() {

    if (millis() - lastUpdate > 1000) {
        lastUpdate = millis();

        if (camera.update()) {

            Serial.println("---- GOPRO STATUS ----");

            Serial.println("Battery: " + String(camera.getBatteryPercent()));
            Serial.println("Recording: " + String(camera.isRecording()));
            Serial.println("Camera: " + camera.getCameraName());
            Serial.println("----------------------");
        }
    }

    if (Serial.available()) {
        String cmd = Serial.readStringUntil('\n');
        parser.handle(cmd);
    }
}
