#include "stdint.h"
#include "RGB.h"
#include "pinControl.h"
extern const uint32_t longPressTime;
extern const uint32_t DoubleClick_MaxInterval;
extern uint8_t BlinkingVariable;

void IdleHandler(RGBLED * rgbLed) {
    ;
}

void ClickHandler(RGBLED * rgbLed) {
    rgbLed->Blinking = 0;
    if (rgbLed->ON) {
        if (++rgbLed->Color >= 4)rgbLed->Color = 0;
    }
}

void DoubleClickHandler(RGBLED * rgbLed) {
    if (rgbLed->ON) rgbLed->Blinking = 1;
}

void LongPressHandler(RGBLED * rgbLed) {
    rgbLed->Blinking = 0;
    rgbLed->ON = !rgbLed->ON;
}

void LedUpdate(RGBLED * rgbled) {

    static uint8_t RedVal;
    static uint8_t GreenVal;
    static uint8_t BlueVal;

    /*
    uint8_t RedVal;
    uint8_t GreenVal;
    uint8_t BlueVal;
     */
    RedVal = rgbled->ON && ((rgbled->Color == RED) || (rgbled->Color == WHITE)) && !(rgbled->Blinking && BlinkingVariable);
    GreenVal = rgbled->ON && ((rgbled->Color == GREEN) || (rgbled->Color == WHITE)) && !(rgbled->Blinking && BlinkingVariable);
    BlueVal = rgbled->ON && ((rgbled->Color == BLUE) || (rgbled->Color == WHITE)) && !(rgbled->Blinking && BlinkingVariable);

    pinWrite(rgbled->redPin.DDR, rgbled->redPin.Bit, RedVal);
    pinWrite(rgbled->greenPin.DDR, rgbled->greenPin.Bit, GreenVal);
    pinWrite(rgbled->bluePin.DDR, rgbled->bluePin.Bit, BlueVal);

}

void LedInit(RGBLED * rgbled) {
    pinDirection(rgbled->redPin.DDR, rgbled->redPin.Bit, OutPut);
    pinDirection(rgbled->greenPin.DDR, rgbled->greenPin.Bit, OutPut);
    pinDirection(rgbled->bluePin.DDR, rgbled->bluePin.Bit, OutPut);

}

EVENT EventDetector(Pin * PushButton) {

    static uint8_t LongPressFlag = 0;
    static uint8_t firstClickFlag = 0;
    static uint32_t tElapsed_LastFallingEdge = 0;
    static uint32_t switchPressingTime = 0;
    EVENT Event = Idle;
    if (pinRead(PushButton->DDR, PushButton->Bit)) {
        if (++switchPressingTime >= longPressTime) {
            LongPressFlag = 1;
            Event = LongPress;
            switchPressingTime = 0;
        }
    }

    onFallingEdge(PushButton,
            switchPressingTime = 0;
    if (!LongPressFlag) {
        if (firstClickFlag) {
            //DoubleClickFlag=1;
            Event = DoubleClick;
                    firstClickFlag = 0;
                    tElapsed_LastFallingEdge = 0;
        } else {
            firstClickFlag = 1;
        }
    } else {
        LongPressFlag = 0;
    }
    )
    if (firstClickFlag) {
        if (++tElapsed_LastFallingEdge >= DoubleClick_MaxInterval) {
            //singleClickFlag=1;
            Event = Click;
            firstClickFlag = 0;
            tElapsed_LastFallingEdge = 0;
        }
    }
    return Event;
}

void BlinkVariable(uint8_t *BlinkingVariable, const uint16_t BlinkingTime) {
    static uint32_t BlinkingTimeCounter = 0;
    if (++BlinkingTimeCounter >= BlinkingTime) {
        BlinkingTimeCounter = 0;
        *BlinkingVariable = !(*BlinkingVariable);
    }

}
void (* EventHandler[4])(RGBLED * rgbled) = {IdleHandler, ClickHandler, DoubleClickHandler, LongPressHandler};