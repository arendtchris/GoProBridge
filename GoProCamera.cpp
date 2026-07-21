#include "GoProCamera.h"
#include <WiFi.h>
#include <HTTPClient.h>

GoProCamera::GoProCamera(const char* ssid,
                         const char* pass,
                         const char* ip)
  : _ssid(ssid),
    _pass(pass),
    _goproIP(ip),
    _raw("")

{

}

bool GoProCamera::begin() {

  Serial.println("---- GOPRO connect ----");

  WiFi.begin(_ssid, _pass);

  unsigned long t = millis();

  while (WiFi.status() != WL_CONNECTED) {
    delay(300);

    if (millis() - t > 15000) {

      Serial.println("Timeout");

      return false;
    }
  }

  Serial.println("WiFi connected");
  return true;
}

String GoProCamera::wifiStatus() {

  switch (WiFi.status()) {
    case WL_NO_SHIELD:       return "WL_NO_SHIELD";
    case WL_IDLE_STATUS:     return "WL_IDLE_STATUS";
    case WL_NO_SSID_AVAIL:   return "WL_NO_SSID_AVAIL";
    case WL_SCAN_COMPLETED:  return "WL_SCAN_COMPLETED";
    case WL_CONNECTED:       return "WL_CONNECTED";
    case WL_CONNECT_FAILED:  return "WL_CONNECT_FAILED";
    case WL_CONNECTION_LOST: return "WL_CONNECTION_LOST";
    case WL_DISCONNECTED:    return "WL_DISCONNECTED";
    default:                 return "UNKNOWN";
  }
}

String GoProCamera::httpGET(const String& url) {

  HTTPClient http;
  http.begin(url);

  int code = http.GET();

  String payload;

  if (code > 0)
    payload = http.getString();

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

String GoProCamera::update() {

  String url = String(_goproIP) + "/gopro/camera/state";

  _raw = httpGET(url);

  if (_raw.length() == 0)
    return "";

  deserializeJson(_doc, _raw);
_raw.replace("\n", "");
  return _raw;
}

String GoProCamera::keepAlive() {
  return httpGET(String(_goproIP) + "/gopro/camera/keep_alive");
}

String GoProCamera::autoPowerDown() {
  return httpGET(String(_goproIP) + "/gopro/camera/setting?option=0&setting=59");
}

String GoProCamera::startRecording() {
  return httpGET(String(_goproIP) + "/gp/gpControl/command/shutter?p=1");
}

String GoProCamera::stopRecording() {
  return httpGET(String(_goproIP) + "/gp/gpControl/command/shutter?p=0");
}

String GoProCamera::setOptions(const String& setting) {
  return httpGET(String(_goproIP) + "/gopro/camera/setting?" + setting);
}

bool GoProCamera::takePhoto() {

  httpGETok(String(_goproIP) + "/gp/gpControl/command/mode?p=1");
  delay(200);

  return httpGETok(String(_goproIP) + "/gp/gpControl/command/shutter?p=1");
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
