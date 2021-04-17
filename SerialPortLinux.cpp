#include "SerialPortLinux.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

SerialPort::SerialPort(const char * portName)
{

	m_portName = portName;
    fd = open(portName, O_RDWR | O_NOCTTY | O_NDELAY);
    
    printf("Open FD %d \n", fd);

    if (fd == -1) {
        perror(portName);
        return ;
    }
    usleep(3500000); // w8 for arduino to reset

    if (tcgetattr(fd, &serial) < 0) {
        perror("Getting configuration");
        return ;
    }

    // Set up Serial Configuration
    serial.c_iflag = 0;
    serial.c_oflag = 0;
    serial.c_lflag = 0;
    serial.c_cflag = 0;

    serial.c_cc[VMIN] = 0;
    serial.c_cc[VTIME] = 0;

    serial.c_cflag = B115200 | CS8 | CREAD;
    //serial.c_cflag = B9600 | CS8 | CREAD;

    tcsetattr(fd, TCSANOW, &serial); // Apply configuration
}

SerialPort::~SerialPort()
{
	closeSerial();
}

int SerialPort::readSerialPort(char* buffer, unsigned int buf_size)
{
	int rcount = read(fd, buffer, buf_size);
	if (rcount < 0) {
		perror("Read");
	}
	buffer[rcount] = '\0';
	return rcount;
}

bool SerialPort::writeSerialPort(const char* buffer, unsigned int buf_size)
{
	int wcount = write(fd, buffer, buf_size);
	if (wcount < 0) {
        perror("Write");
        return false;
    }
    return true;
}

bool SerialPort::isConnected()
{
	return fd != 0;
}

void SerialPort::closeSerial()
{
	close(fd);
}
