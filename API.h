#include "ESPAsyncWebServer.h"
#include <ArduinoWebsockets.h>


// Server API functions
void Rewrite_Config(AsyncWebServerRequest *request);

// Exchange API functions



#define socketAddr "wss://stream.binance.com:9443/ws"

extern String PAIR;

using namespace websockets;

void connectWebSocket();
void printInfo(WebsocketsMessage message);
void onEventsCallback(WebsocketsEvent event, String data);
void poll();
void initWS();
