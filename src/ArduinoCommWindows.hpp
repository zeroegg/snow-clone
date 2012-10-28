#ifndef __ISURC_ARDUINO_COMM_HPP__
#define __ISURC_ARDUINO_COMM_HPP__

<<<<<<< HEAD
#include <cstdlib>
=======
#include <stdio.h>    /* Standard input/output definitions */
#include <stdlib.h>
#include <string.h>   /* String function definitions */
//#include <unistd.h>   /* UNIX standard function definitions */
//#include <fcntl.h>    /* File control definitions */
//#include <errno.h>    /* Error number definitions */
//#include <termios.h>  /* POSIX terminal control definitions */
#include <sys/ioctl.h>
#include <getopt.h>
#include <windows.h>


// note this only works in linux at the moment
>>>>>>> updated ArduinoComm for use with Windows.

namespace isurc {

class ArduinoComm {
public:

   
<<<<<<< HEAD
    

    virtual ~ArduinoComm() {}
    virtual int writeByte(unsigned char b) = 0;
    virtual int writeBytes(unsigned char* buff, size_t len) = 0;
    virtual char readByte() = 0;
    virtual short readShort() = 0;
    virtual bool isOpen() const = 0;
};

=======
    ArduinoComm(const char* serialport, int baud);

    bool open(const char* serialport, int baud);

    ~ArduinoComm();

    int writeByte(unsigned char b);

    int writeBytes(unsigned char* buff, size_t len);

    char readByte(char *buffer); //so far can only return 1 char at a time, even with larger read size. 
    
    short readShort(char *buffer); //not sure



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

inline bool ArduinoComm::open(char *portName, int baud)   //port name i.e. "COM6" then baudrate.
{
DWORD brate;

    switch(baud) {
    case 4800:   brate = CBR_4800;   break;
    case 9600:   brate = CBR_9600;   break;  //probably use this
    case 19200:  brate = CBR_19200;  break;
    case 38400:  brate = CBR_38400;  break;
    case 57600:  brate = CBR_57600;  break;
    case 115200: brate = CBR_115200; break;
    }
    //Not connected yet
    this->connected = false;

    //Try to connect to the given port throuh CreateFile
    this->hSerial = CreateFile(portName,   //COM6 is PortName on my machine for arduino, check serial monitor for portname
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
printf("Connecting...");//informs user basically that this function worked...just wait tho
    //Check if the connection was successfull
    if(this->hSerial==INVALID_HANDLE_VALUE)
    {
        //If not success full display an Error
        if(GetLastError()==ERROR_FILE_NOT_FOUND){

            //Print Error if neccessary
            printf("ERROR: Handle was not attached. Reason: %s not available.\n", portName);

        }
        else
        {
            printf("ERROR!!!");
        }
    }
    else
    {
        //If connected we try to set the comm parameters - bs windows stuff
        DCB dcbSerialParams = {0};

        //Try to get the current
        if (!GetCommState(this->hSerial, &dcbSerialParams))
        {
            //If impossible, show an error, never got this error before however
            printf("failed to get current serial parameters!");
        }
        else
        {
            //Define serial connection parameters for the arduino board - this is necessary 
            dcbSerialParams.BaudRate=brate; //CBR_9600
            dcbSerialParams.ByteSize=8;
            dcbSerialParams.StopBits=ONESTOPBIT;
            dcbSerialParams.Parity=NOPARITY;

             //Set the parameters and check for their proper application
             if(!SetCommState(hSerial, &dcbSerialParams))
             {
                printf("ALERT: Could not set Serial Port parameters");
             }
             else
             {
                 //If everything went fine we're connected
                 this->connected = true;
                 //We wait 2s as the arduino board will be reseting, maybe.
                 Sleep(ARDUINO_WAIT_TIME);
             }
        }
            printf("connected."); //confirms connection, otherwise error is returned if the port doesnt exist
    }

}

bool ArduinoComm::isOpen() const
{
    return fd_ == 0;
}

inline int ArduinoComm::writeByte(unsigned char *buffer)
{
    DWORD bytesSend;
    int nbChar = 1;
    //Try to write the buffer on the Serial port
    if(!WriteFile(this->hSerial, (void *)buffer, nbChar, &bytesSend, 0))
    {
        //In case it don't work get comm error and return false
        ClearCommError(this->hSerial, &this->errors, &this->status);

        return false;
    }
    else
        return true;
}
}

inline int ArduinoComm::writeBytes(unsigned char *buffer, unsigned int nbChar)
{
    DWORD bytesSend;

    //Try to write the buffer on the Serial port
    if(!WriteFile(this->hSerial, (void *)buffer, nbChar, &bytesSend, 0))
    {
        //In case it don't work get comm error and return false
        ClearCommError(this->hSerial, &this->errors, &this->status);

        return false;
    }
    else
        return true;
}

inline int ArduinoComm::readByte(char *buffer)
{
    unsigned int nbChar;
    //Number of bytes we'll have read
    DWORD bytesRead;
    //Number of bytes we'll really ask to read
    unsigned int toRead;

    //Use the ClearCommError function to get status info on the Serial port
    ClearCommError(this->hSerial, &this->errors, &this->status);

    //Check if there is something to read
    if(this->status.cbInQue>0)
    {
        //If there is we check if there is enough data to read the required number
        //of characters, if not we'll read only the available characters to prevent
        //locking of the application.
        if(this->status.cbInQue>nbChar)
        {
            toRead = nbChar;
        }
        else
        {
            toRead = this->status.cbInQue;
        }

        //Try to read the require number of chars, and return the number of read bytes on success
        if(ReadFile(this->hSerial, buffer, toRead, &bytesRead, NULL) && bytesRead != 0)
        {
            return bytesRead;
        }

    }

    //If nothing has been read, or that an error was detected return -1
    return -1;

}

inline int ArduinoComm::readShort(char *buffer, unsigned int nbChar)//not sure if it will work for a short yet.
{
    
    //Number of bytes we'll have read
    DWORD bytesRead;
    //Number of bytes we'll really ask to read
    unsigned int toRead;

    //Use the ClearCommError function to get status info on the Serial port
    ClearCommError(this->hSerial, &this->errors, &this->status);

    //Check if there is something to read
    if(this->status.cbInQue>0)
    {
        //If there is we check if there is enough data to read the required number
        //of characters, if not we'll read only the available characters to prevent
        //locking of the application.
        if(this->status.cbInQue>nbChar)
        {
            toRead = nbChar;
        }
        else
        {
            toRead = this->status.cbInQue;
        }

        //Try to read the require number of chars, and return the number of read bytes on success
        if(ReadFile(this->hSerial, buffer, toRead, &bytesRead, NULL) && bytesRead != 0)
        {
            return bytesRead;
        }

    }

    //If nothing has been read, or that an error was detected return -1
    return -1;

}

>>>>>>> updated ArduinoComm for use with Windows.
}; // end namespace isurc

#endif // __ISURC_ARDUINO_COMM_HPP__

