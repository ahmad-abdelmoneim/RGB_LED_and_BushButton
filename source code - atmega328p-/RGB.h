#ifndef RGBHEADER
#define RGBHEADER
#define onFallingEdge(PIN,DoSomething)\
  static uint8_t PIN##Flag=0;\
  if ( (pinRead(PIN->DDR,PIN->Bit)== 0) && PIN##Flag){\
    DoSomething;\
    PIN##Flag=0;\
  }\
  else if (pinRead(PIN->DDR,PIN->Bit)) {\
    PIN##Flag = 1;\
  }\
  

enum ledColor {RED,BLUE,GREEN,WHITE};
typedef enum {Idle,Click,DoubleClick,LongPress}EVENT;

typedef struct  {
	uint8_t DDR;
	uint8_t Bit;
}Pin;

typedef struct {
	uint8_t Color;
	uint8_t Blinking;
	uint8_t ON;
 	Pin redPin;
	Pin bluePin;
	Pin greenPin;
}RGBLED;

void IdleHandler(RGBLED * rgbLed);
void ClickHandler(RGBLED * rgbLed);
void DoubleClickHandler(RGBLED * rgbLed);
void LongPressHandler(RGBLED * rgbLed);
void LedUpdate(RGBLED * rgbled) ;
void LedInit(RGBLED * rgbled);
EVENT EventDetector(Pin * PushButton);
void BlinkVariable(uint8_t * , const uint16_t );
extern void (* EventHandler[4])(RGBLED * rgbled) ;

#endif


