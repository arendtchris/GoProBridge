#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>

class GoProCamera {
public:
    bool begin(const char* ssid, const char* pass);
    String wifiStatus();

    String update();
    String keepAlive();
    String startRecording();
    String stopRecording();
    bool takePhoto();
    String setOptions(const String& setting);

    int getBatteryPercent();
    bool isRecording();
    String getCameraName();
    int getRemainingTime();
    int getVideoRecordet();
    String getRawStatus();

private:
    String httpGET(const String& url);
    bool httpGETok(const String& url);

    String _raw;
    StaticJsonDocument<8192> _doc;
};
