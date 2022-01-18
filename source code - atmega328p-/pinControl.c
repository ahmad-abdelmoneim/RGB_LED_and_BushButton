
#include <stdint.h>
#include "pinControl.h"

void pinWrite(uint8_t address, uint8_t pinNum, char val) {
    ++address;
    if (val == 0) {
        resetBit(address, pinNum);
    } else if (val == 1) {
        setBit(address, pinNum);
    }
}

uint8_t pinRead(uint8_t address, uint8_t pinNum) {
    --address;
    return *((volatile char *) address) >> pinNum;
}

void pinDirection(uint8_t address, uint8_t pinNum, char val) {
    if (val == 0) {
        resetBit(address, pinNum);
    } else if (val == 1) {
        setBit(address, pinNum);
    }
}

