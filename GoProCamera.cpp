#include "GoProCamera.h"
#include <WiFi.h>
#include <HTTPClient.h>

static const char* GOPRO_IP = "http://10.5.5.9:8080";

bool GoProCamera::begin(const char* ssid, const char* pass) {

    
  WiFi.useStaticBuffers(true);   // gut für den kleinen RAM
  WiFi.mode(WIFI_STA);
  
  // Optional: etwas aggressiveres Verbinden
  WiFi.setTxPower(WIFI_POWER_8_5dBm); // spart Strom, oft stabiler
  
    Serial.println("---- GOPRO connect ----");

    WiFi.begin(ssid, pass);

    unsigned long t = millis();
    while (WiFi.status() != WL_CONNECTED) {
        Serial.println(WiFi.status());
      
        delay(300);
        if (millis() - t > 15000) return false;
    }
    return true;
}


String GoProCamera::wifiStatus(){

  switch (WiFi.status()) {
    case WL_NO_SHIELD:       return "WL_NO_SHIELD";
    case WL_IDLE_STATUS:     return "WL_IDLE_STATUS";
    case WL_NO_SSID_AVAIL:   return "WL_NO_SSID_AVAIL (SSID nicht gefunden)";
    case WL_SCAN_COMPLETED:  return "WL_SCAN_COMPLETED";
    case WL_CONNECTED:       return "WL_CONNECTED";
    case WL_CONNECT_FAILED:  return "WL_CONNECT_FAILED (Falsches Passwort?)";
    case WL_CONNECTION_LOST: return "WL_CONNECTION_LOST";
    case WL_DISCONNECTED:    return "WL_DISCONNECTED";
    default:                 return "Unbekannter Status";
    }
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
    Serial.println(WiFi.status());
    http.begin(url);
    int code = http.GET();
    Serial.println(url);
    Serial.println(http.getString());
    
    http.end();
    return code == 200;
}

String GoProCamera::update() {
    String url = String(GOPRO_IP) + "/gopro/camera/state";
    
    _raw = httpGET(url);

    if (_raw.length() == 0) return "";

    deserializeJson(_doc, _raw);
    return _raw;
    
}

String GoProCamera::keepAlive() {
    String url = String(GOPRO_IP) + "/gopro/camera/keep_alive";
    return  httpGET(url);
}


String GoProCamera::startRecording() {
    return httpGET(String(GOPRO_IP) + "/gp/gpControl/command/shutter?p=1");
}

String GoProCamera::stopRecording() {
    return httpGET(String(GOPRO_IP) + "/gp/gpControl/command/shutter?p=0");
}


String GoProCamera::setOptions(const String& setting) {
    return httpGET(String(GOPRO_IP) + "/gopro/camera/setting?" + setting);
}

bool GoProCamera::takePhoto() {
    httpGETok(String(GOPRO_IP) + "/gp/gpControl/command/mode?p=1");
    delay(200);
    return httpGETok(String(GOPRO_IP) + "/gp/gpControl/command/shutter?p=1");
}

int GoProCamera::getBatteryPercent() {
    return _doc["status"]["70"] | -1;
}

bool GoProCamera::isRecording() {
    return _doc["status"]["8"] == 1;
}

String GoProCamera::getCameraName() {
    return _doc["status"]["30"] | "Unknown";
}

int GoProCamera::getRemainingTime() {
   
    return _doc["status"]["35"].as<int>() / 60;
}
int GoProCamera::getVideoRecordet() {
    return _doc["status"]["37"] | -1;
}
String GoProCamera::getRawStatus() {
    return _raw;
}
