#ifndef __ISURC_ARDUINO_RPC_HPP__
#define __ISURC_ARDUINO_RPC_HPP__

#include "ArduinoComm.hpp"

namespace isurc {

class ArduinoRPC {
public:

    ArduinoRPC(ArduinoComm& comm); 

    ~ArduinoRPC(); 

    void setPWM(int pin, double percent); 

    void setDigital(int pin, bool b); 

    bool readDigital(int pin); 

    double readAnalog(int pin); 

private:
    ArduinoComm& comm_; 

    static double map(double x, double in_min, double in_max, double out_min, double out_max); 

};

inline ArduinoRPC::ArduinoRPC(ArduinoComm& comm) : comm_(comm)
{
    /* do noting */    
}

inline ArduinoRPC::~ArduinoRPC() { /* do nothing */ }

inline void ArduinoRPC::setPWM(int pin, double percent)
{
    // the arduino PWM set value must be in [0, 255]
    const int pwmVal = static_cast<int>(map(percent, 0.0, 100.0, 0.0, 255.0)); 

    // TODO send the value to arduino 
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

// static private
inline double ArduinoRPC::map(double x, double in_min, double in_max, double out_min, double out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

} // end namespace isurc

#endif // __ISURC_ARDUINO_RPC_HPP__
