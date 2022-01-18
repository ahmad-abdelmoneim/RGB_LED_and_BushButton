#define OutPut 1
#define InPut 0
#define BITselector(c,n) (c>>n)&1
#define setBit(byte,pin) *((volatile char*)byte)|=(1<<pin)
#define resetBit(byte,pin) *((volatile char*)byte)&=~(1<<pin)

void pinWrite(uint8_t ,uint8_t ,char);
void pinDirection(uint8_t, uint8_t , char);
uint8_t pinRead(uint8_t ,uint8_t);
