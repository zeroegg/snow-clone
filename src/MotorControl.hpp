#ifndef __ISURC_MOTOR_CONTROL_HPP__
#define __ISURC_MOTOR_CONTROL_HPP__

#include "ArduinoComm.hpp"
#include "ArduinoRPC.hpp"

namespace isurc {

// TODO fill out this class for configuring motors and setting speeds. 
class MotorControl {
public:

    MotorControl(ArduinoComm& comm); 

    ~MotorControl(); 

private:
    ArduinoRPC rpc_; 
};

inline MotorControl::MotorControl(ArduinoComm& comm) : rpc_(comm)
{
    /* do noting */    
}

inline MotorControl::~MotorControl() { /* do nothing */ }

} // end namespace isurc

#endif // __ISURC_MOTOR_CONTROL_HPP__
