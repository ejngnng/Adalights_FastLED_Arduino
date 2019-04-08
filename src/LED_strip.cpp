#include "LED_strip.h"

CRGB adalights[NUM_LEDS];

static uint16_t flashing_interval = 500;
static uint32_t lastTime = 0;

static void led_flashing_red_and_blue();
static void led_strip_black();

void led_strip_setup(){
    FastLED.addLeds<NEOPIXEL, LED_PIN>(adalights, NUM_LEDS);
    uint32_t t=10;
    while(t--){
        led_flashing_red_and_blue();
    }
    led_strip_black();
}


static void led_flashing_red_and_blue(){
    uint32_t now = millis();
    if(now - lastTime < flashing_interval){
        for(uint16_t i=0; i<NUM_LEDS; i++){
            adalights[i] = CRGB::Red;
            FastLED.show();
        }
    }else if(now - lastTime >= flashing_interval && now - lastTime < 2*flashing_interval){
        for(uint16_t i=0; i<NUM_LEDS; i++){
            adalights[i] = CRGB::Blue;
            FastLED.show();
        }
    }else{
        lastTime = now;
    }

}

static void led_strip_black(){
    for(uint16_t i=0; i<NUM_LEDS; i++){
        adalights[i] = CRGB::Black;
        FastLED.show();
    }
}