#include "API.h"
#include "config.h"
#include "ESPAsyncWebServer.h"
#include <ArduinoJson.h>
#include "display.h"
#include <ArduinoWebsockets.h>

using namespace websockets;
WebsocketsClient client;


// Server API function
void Rewrite_Config(AsyncWebServerRequest *request) {


  if (!request->hasArg("config")) {
    request->send_P(400, "application/json", "{\"error\":\"Empty Body\"}");
    return;
  }

  String body = request->arg("config");
  DynamicJsonDocument doc(200);
  DeserializationError err = deserializeJson(doc, body);
  if (err) {
    request->send_P(400, "application/json", "{\"error\":\"Invalid Json\"}");
    return;
  }


  if (!write_config("config.json", body)) {
    request->send_P(400, "application/json", "{\"error\":\"Internal Server Error\"}");
    return;
  }

  request->send_P(200, "application/json", "{\"error\":null");
}




// Exchange API functions

void initWS() {
  client.onMessage(printInfo);
  client.onEvent(onEventsCallback);
}

void connectWebSocket() {
  client.connect(socketAddr);
  client.send(String("{\"method\":\"SUBSCRIBE\",\"params\":[\"") + PAIR +  String("\"],\"id\":1}"));
}

void onEventsCallback(WebsocketsEvent event, String data) {
  if (event == WebsocketsEvent::ConnectionOpened) {
    printNewMessage("Connected to Server!");
    clearDisp();
    displayLogo(PAIR.substring(0, 3));
  } else if (event == WebsocketsEvent::ConnectionClosed) {
    printNewMessage("Connection Closed!");
    connectWebSocket();
  }
}


void printInfo(WebsocketsMessage message) {
  DynamicJsonDocument resp(300);

  DeserializationError err = deserializeJson(resp, message.data());
  if (err) {
    printNewMessage("JSON Read Error");
  } else {
    String r = resp["p"].as<const char*>();
    float number = r.toFloat();
    if (number == 0) {
      return;
    }
    displayPrice(String(number));
  }
}


void poll() {
  client.poll();
}
