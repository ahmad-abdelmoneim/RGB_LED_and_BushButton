#include <stdint.h>
#include "pinControl.h"
#include "RGB.h"
#include "TMR1.h"
#include <avr/io.h>
#include <avr/interrupt.h>

const uint32_t longPressTime = 200; //400
const uint32_t DoubleClick_MaxInterval = 50; //30
const uint16_t BlinkingTime = 20; //50
uint8_t BlinkingVariable = 0;
uint16_t TMR1_IR_Freq = 200;

volatile RGBLED myLed = {RED, 0, 0,
    {(uint8_t) & DDRC, 3},
    {(uint8_t) & DDRC, 4},
    {(uint8_t) & DDRC, 5}};
//volatile RGBLED myLed2 = {BLUE,0,0,{(uint8_t)&DDRD,0},{(uint8_t)&DDRD,1},{(uint8_t)&DDRD,2}};
Pin PushButton = {(uint8_t) & DDRB, 1};

int main() {
    cli();
    pinDirection(PushButton.DDR, PushButton.Bit, InPut);
    LedInit(&myLed);
    //LedInit(&myLed2);
    TMR1_Init();
    sei();
    while (1) {
        LedUpdate(&myLed);
        // LedUpdate(&myLed2);
    }
    return 0;
}

ISR(TIMER1_COMPA_vect) {
    EVENT newEvent = EventDetector(&PushButton);
    if (newEvent != Idle) {
        EventHandler[newEvent](&myLed);
        //EventHandler[newEvent](&myLed2);
    }
    BlinkVariable(&BlinkingVariable, BlinkingTime);
}
