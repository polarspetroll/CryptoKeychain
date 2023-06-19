#include "Arduino.h"

void initDisplay();

void loading(int timeout);

void printNewMessage(String msg);

void displayLogo(String symbol);

void show_symbol(const unsigned char* s, int w, int h);

void displayPrice(String price);

void displayStatus();

void clearDisp(void);
