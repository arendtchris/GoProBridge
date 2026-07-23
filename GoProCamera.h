#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

class GoProCamera {
public:
    GoProCamera(const char* ip = "http://10.5.5.9:8080");

    bool begin(const char* ssid, const char* pass);

    String wifiStatus();

    String update();
    String keepAlive();
    String autoPowerDown();

    String startRecording();
    String stopRecording();
    bool takePhoto();

    String setOptions(const int setting, const int option);

    int getBatteryPercent();
    bool isRecording();
    String getCameraName();
    int getRemainingTime();
    int getVideoRecordet();
    String getRawStatus();

private:
    String httpGET(const String& url);
    bool httpGETok(const String& url);

    const char* _ssid;
    const char* _pass;
    const char* _goproIP;

    String _raw;
    StaticJsonDocument<8192> _doc;
};
