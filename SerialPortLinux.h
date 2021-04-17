#pragma once
#include <string>
#include <termios.h>

class SerialPort
{
public:
	explicit SerialPort(const char* portName);
	~SerialPort();
	
	int readSerialPort(char* buffer, unsigned int buf_size);
	bool writeSerialPort(const char* buffer, unsigned int buf_size);
	bool isConnected();
	void closeSerial();
	
private:
	std::string m_portName = "/dev/ttyUSB0";
    struct termios serial;
    int fd = 0;
};
