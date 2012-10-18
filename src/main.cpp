#include "ArduinoRPC.hpp"
#include "ArduinoComm.hpp"
#include "MotorControl.hpp"

using namespace isurc; 

int main(int argc, char** argv) 
{
	ArduinoComm comm("/dev/ttyUSB0", 9600); 
	ArduinoRPC rpc(comm);

	rpc.setPWM(0, 1.0); 

	MotorControl mc(comm); 

	return 0;
}
