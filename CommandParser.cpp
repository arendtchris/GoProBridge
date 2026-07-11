#include "CommandParser.h"

void CommandParser::handle(GoProCamera camera, String cmd) {

    cmd.trim();

    if (cmd == "REC=REC_ON") {
        Serial.println("START_RECORD");
        camera.startRecording();
    }
    else if (cmd == "REC=REC_OFF") {
        Serial.println("STOP_RECORD");
        camera.stopRecording();
    }
    else if (cmd == "REC=PHOTO") {
        Serial.println("TAKE_PHOTO");
        camera.takePhoto();
    }
    else if (cmd == "REC=IDLE") {
        Serial.println("IDLE");
    }
}
