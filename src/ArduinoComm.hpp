#ifndef __ISURC_ARDUINO_COMM_HPP__
#define __ISURC_ARDUINO_COMM_HPP__

#include <stdio.h>    /* Standard input/output definitions */
#include <stdlib.h>
#include <string.h>   /* String function definitions */
#include <unistd.h>   /* UNIX standard function definitions */
#include <fcntl.h>    /* File control definitions */
#include <errno.h>    /* Error number definitions */
#include <termios.h>  /* POSIX terminal control definitions */
#include <sys/ioctl.h>
#include <getopt.h>

// note this only works in linux at the moment

namespace isurc {

class ArduinoComm {
public:

    ArduinoComm();

    /**
     * takes the string name of the serial port (e.g. "/dev/tty.usbserial","COM1")
     * and a baud rate (bps) and connects to that port at that speed and 8N1.
     * opens the port in fully raw mode so you can send binary data.
     */
    ArduinoComm(const char* serialport, int baud);

    bool open(const char* serialport, int baud);

    ~ArduinoComm();

    int writeByte(unsigned char b);

    int writeBytes(unsigned char* buff, size_t len);

    char readByte(); 

    bool isOpen() const;

private:
    int fd_;

};

inline ArduinoComm::ArduinoComm() : fd_(0) { /* do nothing */ }

inline ArduinoComm::ArduinoComm(const char* serialport, int baud) : fd_(0)
{
    open(serialport, baud);
}

inline ArduinoComm::~ArduinoComm()
{
    close(fd_);
}

inline bool ArduinoComm::open(const char* serialport, int baud)
{
    struct termios toptions;

    //fd_ = open(serialport, O_RDWR | O_NOCTTY | O_NDELAY);
    fd_ = open(serialport, O_RDWR | O_NOCTTY);

    if (fd_ == -1)  {
      printf("init_serialport: Unable to open port ");
      fd_ = 0;
      return false;
    }
    if (tcgetattr(fd_, &toptions) < 0) {
      printf("init_serialport: Couldn't get term attributes");
      fd_ = 0;
      return false;
    }

    speed_t brate = baud; // let you override switch below if needed

    switch(baud) {
    case 4800:   brate = B4800;   break;
    case 9600:   brate = B9600;   break;
    case 19200:  brate = B19200;  break;
    case 38400:  brate = B38400;  break;
    case 57600:  brate = B57600;  break;
    case 115200: brate = B115200; break;
    }

    cfsetispeed(&toptions, brate);
    cfsetospeed(&toptions, brate);

    // 8N1
    toptions.c_cflag &= ~PARENB;
    toptions.c_cflag &= ~CSTOPB;
    toptions.c_cflag &= ~CSIZE;
    toptions.c_cflag |= CS8;

    // no flow control
    toptions.c_cflag &= ~CRTSCTS;
    toptions.c_cflag |= CREAD | CLOCAL;  // turn on READ & ignore ctrl lines
    toptions.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl
    toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
    toptions.c_oflag &= ~OPOST; // make raw

    // see: http://unixwiz.net/techtips/termios-vmin-vtime.html
    toptions.c_cc[VMIN]  = 0;
    toptions.c_cc[VTIME] = 20;

    if( tcsetattr(fd_, TCSANOW, &toptions) < 0) {
        printf("init_serialport: Couldn't set term attributes");
        fd_ = 0;
        return false;
    }
    return true;
}

bool ArduinoComm::isOpen() const
{
    return fd_ == 0;
}

inline int ArduinoComm::writeByte(unsigned char b)
{
    return write(fd_, &b, 1);
}

inline int ArduinoComm::writeBytes(unsigned char* buff, size_t len)
{
    return write(fd_, buff, len);
}

}; // end namespace isurc

#endif // __ISURC_ARDUINO_COMM_HPP__
