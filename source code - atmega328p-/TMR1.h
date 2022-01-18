#ifndef TMR1HEADER
#define TMR1HEADER
#define _CKPS 64
#define CKPS_0 0
#define CKPS_1 1
#define CKPS_8 2
#define CKPS_64 3
#define CKPS_256 4
#define CKPS_1024 5
#define F_CPU 16000000

#define CTC_MODE TCCR1B|=(1<<WGM12)
#define CTC_INT_EN TIMSK1|=(1<<OCIE1A)
#define CTC_INT_DIS TIMSK1&=~(1<<OCIE1A)
#define Set_TMR1_PS(PS) TCCR1B=(TCCR1B&0b11111000)|PS
void setTMR1_interrupt_freq(uint16_t);
void TMR1_Init();

#endif


