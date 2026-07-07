#include "GoProCamera.h"
#include <WiFi.h>
#include <HTTPClient.h>

static const char* GOPRO_IP = "http://10.5.5.9";

bool GoProCamera::begin(const char* ssid, const char* pass) {

    
  WiFi.useStaticBuffers(true);   // gut für den kleinen RAM
  WiFi.mode(WIFI_STA);
  
  // Optional: etwas aggressiveres Verbinden
  WiFi.setTxPower(WIFI_POWER_8_5dBm); // spart Strom, oft stabiler
  
    
    WiFi.begin(ssid, pass);

    unsigned long t = millis();
    while (WiFi.status() != WL_CONNECTED) {
        delay(300);
        if (millis() - t > 15000) return false;
    }
    return true;
}

String GoProCamera::httpGET(const String& url) {
    HTTPClient http;
    http.begin(url);
    int code = http.GET();
    String payload = (code > 0) ? http.getString() : "";
    http.end();
    return payload;
}

bool GoProCamera::httpGETok(const String& url) {
    HTTPClient http;
    http.begin(url);
    int code = http.GET();
    http.end();
    return code == 200;
}

bool GoProCamera::update() {
    String url = String(GOPRO_IP) + "/gp/gpControl/status";
    _raw = httpGET(url);

    if (_raw.length() == 0) return false;

    deserializeJson(_doc, _raw);
    return true;
}

bool GoProCamera::startRecording() {
    return httpGETok(String(GOPRO_IP) + "/gp/gpControl/command/shutter?p=1");
}

bool GoProCamera::stopRecording() {
    return httpGETok(String(GOPRO_IP) + "/gp/gpControl/command/shutter?p=0");
}

bool GoProCamera::takePhoto() {
    httpGETok(String(GOPRO_IP) + "/gp/gpControl/command/mode?p=1");
    delay(200);
    return httpGETok(String(GOPRO_IP) + "/gp/gpControl/command/shutter?p=1");
}

int GoProCamera::getBatteryPercent() {
    return _doc["status"]["23"] | -1;
}

bool GoProCamera::isRecording() {
    return _doc["status"]["8"] == 1;
}

String GoProCamera::getCameraName() {
    return _doc["status"]["30"] | "Unknown";
}

int GoProCamera::getRemainingTime() {
    return _doc["status"]["37"] | -1;
}

String GoProCamera::getRawStatus() {
    return _raw;
}
