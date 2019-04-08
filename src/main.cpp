#include "LED_strip.h"
#include "ada.h"

static const uint8_t prefix[] = {'A', 'd', 'a'};
extern CRGB adalights[NUM_LEDS];



void setup(){
  led_strip_setup();
  ada_setup();
}


void loop(){
  ada_loop();
}