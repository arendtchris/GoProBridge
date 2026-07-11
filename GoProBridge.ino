#include "GoProCamera.h"
#include "StatusDecoder.h"
#include "CommandParser.h"
#include "config.h"

GoProCamera camera;
StatusDecoder decoder;
CommandParser parser;

HardwareSerial fcSerial(0);        // UART0 ESP32-C3
const int baudRate = 115200;

// Empfangspuffer
char rxBuffer[150];
uint8_t rxIndex = 0;

unsigned long lastUpdate = 0;

void setup() {
    Serial.begin(115200);
    fcSerial.begin(baudRate, SERIAL_8N1, 20, 21);
    delay(1000);
    camera.begin(WIFI_SSID, WIFI_PASS);
}

void loop() {

    if (millis() - lastUpdate > 1000) {
        lastUpdate = millis();


        //camera.startRecording();
        //delay(10000);
        //camera.stopRecording();


        if (camera.update()) {

            Serial.println("---- GOPRO STATUS ----");
            Serial.println("Battery: " + String(camera.getBatteryPercent()));
            Serial.println("VideoRecordet: " + String(camera.getVideoRecordet()));
            Serial.println("RemainingTime: " + String(camera.getRemainingTime()));
            Serial.println("Recording: " + String(camera.isRecording()));
            Serial.println("Camera: " + camera.getCameraName());
            Serial.println("----------------------");
        }
    }

    if (fcSerial.available()) {
        String cmd = fcSerial.readStringUntil('\n');
        
        parser.handle( camera, cmd);
    }
}
