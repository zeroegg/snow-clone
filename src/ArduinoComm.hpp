#ifndef __ISURC_ARDUINO_COMM_HPP__
#define __ISURC_ARDUINO_COMM_HPP__

#include <cstdlib>

namespace isurc {

class ArduinoComm {
public:

    //ArduinoComm();

    /**
     * takes the string name of the serial port (e.g. "/dev/tty.usbserial","COM1")
     * and a baud rate (bps) and connects to that port at that speed and 8N1.
     * opens the port in fully raw mode so you can send binary data.
     */
    //ArduinoComm(const char* serialport, int baud);

    virtual ~ArduinoComm() {}
    virtual int writeByte(unsigned char b) = 0;
    virtual int writeBytes(unsigned char* buff, size_t len) = 0;
    virtual char readByte() = 0;
    virtual short readShort() = 0;
    virtual bool isOpen() const = 0;
};

}; // end namespace isurc

#endif // __ISURC_ARDUINO_COMM_HPP__
