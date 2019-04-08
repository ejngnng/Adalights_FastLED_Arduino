#include "ada.h"
#include "LED_strip.h"

uint8_t RECV_FLAG = 0;
uint8_t recv_buffer[128] = {0};

extern CRGB adalights[NUM_LEDS];

#define DEBUG

ada_state g_ada_state;

static uint8_t ada_header[6];
static uint8_t ada_header_buffer[6];

static uint16_t current_led = 0;

static void process_ada_wait(ada_state *state);
static void process_ada_header(ada_state *state);
static void process_ada_data(ada_state *state);

void ada_setup(){
    Serial.begin(BAUD_RATE);
    Serial.print("Ada\n");
    memset(ada_header, 0, sizeof(uint8_t) * 6);
    memset(ada_header_buffer, 0, sizeof(uint8_t) * 6);
    ada_header_construct(ada_header, NUM_LEDS);
    g_ada_state = STATE_WAIT;
}

void ada_loop(){
    switch (g_ada_state)
    {
        case STATE_WAIT:
            process_ada_wait(&g_ada_state);
            break;
        case STATE_HEADER:
            process_ada_header(&g_ada_state);
            break;
        case STATE_DATA:
            process_ada_data(&g_ada_state);
            break;
        default:
            break;
    }
}

// hyperion adalight code
// header[3] = ((led_size - 1) >> 8) & 0xFF;    // LED count high byte
// header[4] = (led_size - 1) & 0xFF;           // LED count low byte
// header[5] = header[3] ^ header[4] ^ 0x55;    // Checksum
void ada_header_construct(uint8_t *header, uint16_t led_size){
    memset(header, 0, sizeof(uint8_t) * 6);
    header[0] = 'A';
    header[1] = 'a';
    header[2] = 'd';
    header[3] = ((led_size - 1) >> 8) & 0xFF;
    header[4] = (led_size - 1) & 0xFF;
    header[5] = header[3] ^ header[4] ^ 0x55;
}

static void process_ada_wait(ada_state *state){
    if(*state == STATE_WAIT){
        if(Serial.available()>0 ){
           int readSerial = Serial.read();      // Read one character
        
            if (readSerial == ada_header[0]){
                *state = STATE_HEADER;
            }
        }
    }
}

static void process_ada_header(ada_state *state){
    if(*state == STATE_HEADER){
        if( Serial.available() > sizeof(ada_header) - 2){
          Serial.readBytes(ada_header_buffer, sizeof(ada_header) - 1);
          
          for( int Counter = 0; Counter < sizeof(ada_header) - 1; Counter++){
            if( ada_header_buffer[Counter] == ada_header[Counter+1]){
              *state = STATE_DATA;     
              current_led = 0;       
            }else {
              *state = STATE_WAIT;    
              break;                 
            } 
          }
      }
    }
}

static void process_ada_data(ada_state *state){
    if( Serial.available() > 2 ){
        uint8_t buffer[3] = {0};
        Serial.readBytes(buffer, 3);   // Abuse buffer to temp store 3 charaters
        adalights[current_led].red = buffer[0];
        adalights[current_led].green = buffer[1];
        adalights[current_led].blue = buffer[2];
        current_led ++;
    }

    if(current_led > NUM_LEDS){
        FastLED.show();            
        *state = STATE_WAIT;
        current_led = 0;                          
    }
}