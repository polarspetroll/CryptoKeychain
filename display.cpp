#include "display.h"
#include "heltec.h"
#include "logo.h"
#include <ESP8266WiFi.h>


void initDisplay() {
  Heltec.begin(true, false);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();
}

void printNewMessage(String msg) {
  clearDisp();
  Heltec.display->drawString(0, 0, msg);
  Heltec.display->display();
}

void loading(int timeout) {
  int j = timeout / 100;

  for (int i = 0; i < 100; i++) {
    Heltec.display->setPixel(i, 30);
    Heltec.display->display();
    delay(j);
  }

}

void displayLogo(String symbol) {
  if (symbol.equals("btc")) {
    show_symbol(BTC, 30, 30);
  }
  else if (symbol.equals("eth")) {
    show_symbol(ETH, 53, 30);
  }
  else if (symbol.equals("xmr")) {
    show_symbol(XMR, 30, 30);
  }
  else if (symbol.equals("ltc")) {
    show_symbol(LTC, 30, 30);
  }
  else if (symbol.equals("xrp")) {
    show_symbol(XRP, 30, 30);
  }
}

void show_symbol(const unsigned char*s, int w, int h) {
  Heltec.display->drawXbm(87, 0, w, h, s);
  Heltec.display->display();
}


void displayPrice(String price) {
  Heltec.display->setColor(BLACK);
  int w = price.length();
  Heltec.display->fillRect(0, 0, w * 9, 16);

  // Redraw the updated number at the desired location
  Heltec.display->setColor(WHITE);
  Heltec.display->setFont(ArialMT_Plain_16);
  Heltec.display->drawString(0, 0, price);
  Heltec.display->display();
}

void displayStatus() {
  Heltec.display->drawXbm(0, 18, 15, 15, WIFI);
  Heltec.display->drawString(20, 18, WiFi.SSID());
  Heltec.display->display();
}

void clearDisp(void) {
  Heltec.display->clear();
}
