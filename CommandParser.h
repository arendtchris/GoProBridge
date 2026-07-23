#pragma once
#include <Arduino.h>
#include "GoProCamera.h"
#include <ArduinoJson.h>
class CommandParser {
public:
    void handle(GoProCamera camera, String cmd);
};
