#include "config.h"
#include "LittleFS.h"
#include <ArduinoJson.h>

boolean write_config(String file_name, String content) {
  LittleFS.begin();
  File f = LittleFS.open(file_name, "w");
  if (!f) {
    return false;
  }

  f.print(content);
  f.close();

  LittleFS.end();
  return true;
}



DynamicJsonDocument read_config(String config_file) {
  LittleFS.begin();
  DynamicJsonDocument doc(200);
  
  File f = LittleFS.open(config_file, "r");
  if (!f) {
    return doc;
  }
  String json_str;
  while (f.available()) {
    json_str += (char) f.read();
  }

  
  DeserializationError err = deserializeJson(doc, json_str);

  if (err) {
    return doc;
  }

  f.close();
  LittleFS.end();
  return doc;


}
