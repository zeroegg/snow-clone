#ifndef __ISURC_MOTOR_CONTROL_HPP__
#define __ISURC_MOTOR_CONTROL_HPP__

#include "ArduinoComm.hpp"
#include "ArduinoRPC.hpp"

namespace isurc {

// TODO fill out this class for configuring motors and setting speeds. 
class MotorControl {
public:

    typedef enum { LEFT = 0, RIGHT = 1, MOTOR_COUNT = 2 } Motor; 

    MotorControl(ArduinoComm& comm); 

    ~MotorControl(); 

    /* a rate is the the range [-1.0, 1.0] */
    void setSpeed(double rate, Motor m); 
    void setSpeed(double rate); 
    double getSpeed(Motor m); 
    void halt(); 

private:
    ArduinoRPC rpc_; 

    double rates_[MOTOR_COUNT];

    char pins_[MOTOR_COUNT];
};

inline MotorControl::MotorControl(ArduinoComm& comm) : rpc_(comm)
{
    rates_[LEFT] = 0.0; 
    rates_[RIGHT] = 0.0; 
    
    // TODO get from config file
    pins_[LEFT] = 7; 
    pins_[RIGHT] = 8; 
}

inline MotorControl::~MotorControl() { /* do nothing */ }


inline void MotorControl::setSpeed(double rate, Motor m)
{
    // TODO bounds checking
    rpc_.setPWM(pins_[m], ArduinoRPC::map(rate, -1.0, 1.0, 0.0, 1.0));    
    rates_[m] = rate; 
}

inline void MotorControl::setSpeed(double rate)
{
    // TODO bounds checking
    const double val = ArduinoRPC::map(rate, -1.0, 1.0, 0.0, 1.0);
    rpc_.setPWM(pins_[LEFT], val);
    rates_[LEFT] = rate; 
    rpc_.setPWM(pins_[RIGHT], val);
    rates_[RIGHT] = rate; 
}

inline double MotorControl::getSpeed(Motor m)
{
    return rates_[m];
}

inline void MotorControl::halt()
{
    setSpeed(0.0);  
}

} // end namespace isurc


#endif // __ISURC_MOTOR_CONTROL_HPP__
