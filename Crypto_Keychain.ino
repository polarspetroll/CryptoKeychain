#include "ESPAsyncWebServer.h"
#include <ESP8266WiFi.h>
#include "config.h"
#include "API.h"
#include "display.h"
#include <Wire.h>
#include <ArduinoJson.h>


#include "heltec.h"

String PAIR = "btcusdt@trade";
const char* server_ssid = "Crypto Keychain";
const char* server_password = "##123CryptoKeychain123##";
IPAddress local_IP(192, 168, 4, 22);
IPAddress gateway(192, 168, 4, 9);
IPAddress subnet(255, 255, 255, 0);
AsyncWebServer APIServer(80);
const int wifi_timeout = 8000;

void setup() {
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(server_ssid, server_password);
  APIServer.begin();
  

  APIServer.on("/api/rewrite_config", HTTP_POST, Rewrite_Config);



  initDisplay();
  Serial.begin(115200);
  
  DynamicJsonDocument conf = read_config("config.json");
  if (conf.isNull()) {
    printNewMessage("Error: Failed to read configuration file");
    return;
  }


  /* Checks all available wifi networks */
  JsonArray wifiArray = conf["networks"].as<JsonArray>();
  Serial.begin(9600);

  printNewMessage("Connecting to WiFi network");

  for (int i = 0; i < i < wifiArray.size(); i++) {
    const char* ssid = wifiArray[i]["ssid"].as<const char*>();
    const char* password = wifiArray[i]["password"].as<const char*>();
    Serial.println(ssid);
    Serial.println(password);
    
    WiFi.begin(ssid, password);
    
    loading(wifi_timeout); // timeout
    
    if (WiFi.status() == WL_CONNECTED) {
      printNewMessage(String("Connected to ") + String(ssid) + String("!"));
      break;
    }

    if (WiFi.status() != WL_CONNECTED && i + 1 == wifiArray.size()) {
      printNewMessage("Wi-Fi connection failed");
      return;
    }

  }
  /****************************************/
  initWS();
  connectWebSocket();
  

}

void loop() {
  poll();
}
