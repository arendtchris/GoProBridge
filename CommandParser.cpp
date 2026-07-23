#include "CommandParser.h"
StaticJsonDocument<8192> jsonDoc;


String setting;
String option;
String ssid;
String pass;

void CommandParser::handle(GoProCamera camera, String cmd) {

  cmd.trim();
  Serial.println("raw fc tx message" + cmd);
  deserializeJson(jsonDoc, cmd);



  if (jsonDoc["setting"] == 0) {



    if (jsonDoc["option"] == 0) {
      Serial.println("connenct");
      /*if (camera.begin(jsonDoc["ssid"], jsonDoc["pass"]) {
        camera.autoPowerDown();
        }*/
      camera.begin(jsonDoc["ssid"], jsonDoc["pass"]);
  camera.autoPowerDown();

    } else if (jsonDoc["option"] == 1) {
      Serial.println("update");
      //   Serial.println(camera.update());
    }



  } else if (jsonDoc["setting"] == 8) {
    if (jsonDoc["option"] == 0) {
      Serial.println("STOP_RECORD");
      camera.stopRecording();
    } else if (jsonDoc["option"] == 1) {
      Serial.println("START_RECORD");
      camera.startRecording();
    } else if (jsonDoc["option"] == 2) {
      Serial.println("TAKE_PHOTO");
      camera.takePhoto();
    }

  } else {


    Serial.println( camera.setOptions(jsonDoc["setting"]  , jsonDoc["option"]));
  }

}
