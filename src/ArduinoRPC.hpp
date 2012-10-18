#ifndef __ISURC_ARDUINO_RPC_HPP__
#define __ISURC_ARDUINO_RPC_HPP__

#include "ArduinoComm.hpp"
#include "commands.h"

namespace isurc {

class ArduinoRPC {
public:

    ArduinoRPC(ArduinoComm& comm); 

    ~ArduinoRPC(); 

    /**
     * @param percent between 0.0 and 1.0
     */
    void setPWM(int pin, double percent); 

    void setDigital(int pin, bool b); 

    bool readDigital(int pin); 

    double readAnalog(int pin); 

    static double map(double x, double in_min, double in_max, double out_min, double out_max); 

private:
    ArduinoComm& comm_; 


};

inline ArduinoRPC::ArduinoRPC(ArduinoComm& comm) : comm_(comm)
{
    /* do noting */    
}

inline ArduinoRPC::~ArduinoRPC() { /* do nothing */ }

inline void ArduinoRPC::setPWM(int pin, double percent)
{
    // TODO bounds checking
    
    // the arduino PWM set value must be in [0, 255]
    const int pwmVal = static_cast<int>(map(percent, 0.0, 1.0, 0.0, 255.0)); 

    // send the value to arduino
    // void CODE_SET_PWM(char pin, unsigned char pwmVal [0, 255]) 
    comm_.writeByte(CODE_SET_PWM); 
    comm_.writeByte(pin); 
    comm_.writeByte(pwmVal);

/* code sample for arduino side
    char cmd = Serial.read();
    switch (cmd)
    {
    case CODE_SET_PWM:
        char pin = Serial.read(); 
        char val = Serial.read(); 
        analogWrite(pin, value); 
        break; 
    case SOME_OTHER_CODE:
        break;

        jpsteffe
        mmr

    }  */
}

inline void ArduinoRPC::setDigital(int pin, bool b)
{
    // TODO
}

inline bool ArduinoRPC::readDigital(int pin)
{
    // TODO 
    return false; 
}

inline double ArduinoRPC::readAnalog(int pin)
{
    // TODO 
    return 0.0;
}

// static public
inline double ArduinoRPC::map(double x, double in_min, double in_max, double out_min, double out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

} // end namespace isurc

#endif // __ISURC_ARDUINO_RPC_HPP__
