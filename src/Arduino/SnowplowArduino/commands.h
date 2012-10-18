#ifndef __COMMANDS__
#define __COMMANDS__

#define CODE_SET_PWM        0x01 // void (char pin, unsigned char pwmVal [0, 255])
#define CODE_SET_DIGITAL    0x02 // void (char pin, char b)
#define CODE_READ_DIGITAL   0x03 // char (char pin)
#define CODE_READ_ANALOG    0x04 // short (char pin)
#define CODE_SET_PIN_INOUT  0x05 // void (char pin, char in/out)

#endif // __COMMANDS__
