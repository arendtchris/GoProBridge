#include "StatusDecoder.h"

String StatusDecoder::decode(int key, int value) {

    switch (key) {
        case 8:  return "Recording: " + String(value);
        case 23: return "Battery: " + String(value) + "%";
        case 30: return "Camera: HERO11";
        case 37: return "Remaining: " + String(value);
        case 1:  return "Power: " + String(value);
        default: return "Key " + String(key) + ": " + String(value);
    }
}
