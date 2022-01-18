#include <stdint.h>
#include "TMR1.h"
#include <avr/io.h>

extern uint16_t TMR1_IR_Freq;

void setTMR1_interrupt_freq(uint16_t freq) {
    OCR1A = ((F_CPU) / (freq * _CKPS)) - 1;
}

void TMR1_Init() {
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;
    CTC_MODE;
    CTC_INT_EN;
    setTMR1_interrupt_freq(TMR1_IR_Freq);
    Set_TMR1_PS(CKPS_64);
}
