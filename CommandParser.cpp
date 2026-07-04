#include "CommandParser.h"

void CommandParser::handle(String cmd) {

    cmd.trim();

    if (cmd == "REC_ON") {
        Serial.println("START_RECORD");
    }
    else if (cmd == "REC_OFF") {
        Serial.println("STOP_RECORD");
    }
    else if (cmd == "PHOTO") {
        Serial.println("TAKE_PHOTO");
    }
}
