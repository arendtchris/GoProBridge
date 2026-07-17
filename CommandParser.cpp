#include "CommandParser.h"

void CommandParser::handle(GoProCamera camera, String cmd) {

    cmd.trim();


    if (cmd == "option=0&setting=0") {
        Serial.println(camera.keepAlive());
     }
      else if (cmd == "option=1&setting=0") {
         Serial.println(camera.update());
    }
     else if (cmd == "option=1&setting=8") {
        Serial.println("START_RECORD");
        camera.startRecording();
    }
    else if (cmd == "option=0&setting=8") {
        Serial.println("STOP_RECORD");
        camera.stopRecording();
    }
    else if (cmd == "option=2&setting=8") {
        Serial.println("TAKE_PHOTO");
        camera.takePhoto();
    }
    else {
       Serial.println(cmd);
      Serial.println( camera.setOptions(cmd));
    }
}
