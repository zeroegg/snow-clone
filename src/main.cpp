#include "ArduinoRPC.hpp"
#include "ArduinoComm.hpp"
#include "ArduinoCommLinux.hpp"
#include "MotorControl.hpp"

using namespace isurc; 

int main(int argc, char** argv) 
{
	ArduinoComm* comm;
	comm = new ArduinoCommLinux("/dev/ttyUSB0", 9600); 
	
	ArduinoRPC rpc(*comm);

	rpc.setPWM(0, 1.0); 

	// TODO read the pins from a config file 
	MotorControl mc(*comm, 7, 8); 

	return 0;
}
