#pragma once
#include <Arduino.h>

class StatusDecoder {
public:
    String decode(int key, int value);
};
