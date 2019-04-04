#include "ada.h"
#include "LED_strip.h"

uint8_t RECV_FLAG = 0;
uint8_t recv_buffer[128] = {0};

extern CRGB adalights[NUM_LEDS];

#define DEBUG

static uint8_t ada_header[] = {0x41,    // A 
                               0x64,    // d
                               0x61,    // a
                               0x00,        
                               0x6F,    // NUM_LEDS -1
                               0x3A};   // 

void ada_setup(){
    Serial.begin(BAUD_RATE);
    Serial.print("Ada\n");
}

void ada_loop(){
    if(RECV_FLAG == 1){
        RECV_FLAG = 0;
        if(Serial.available() > 0){
            int num = Serial.available();
            if(num > 0){
                uint8_t len = Serial.readBytes(recv_buffer, num);
                Serial.print("len: ");
                Serial.print(len);
                Serial.print("num: ");
                Serial.println(num);
                for(uint8_t i=0; i<num; i++){
                    Serial.println(recv_buffer[i], HEX);
                }
            }
        }
    }
}


void serialEvent(){
    if(Serial.available() > 0){
        RECV_FLAG = 1;
    }
}