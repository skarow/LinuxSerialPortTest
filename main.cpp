#include "SerialPortLinux.h"

int main()
{
	SerialPort port("/dev/ttyUSB0");
	
	std::string str = "5*1000/0/01!";
    char buffer[255];
	
	for ( int i = 0; i < 4; ++ i) 
    {
		str = str + std::to_string(i);
		port.writeSerialPort(str.c_str(), str.length());
		
		int read = 0;
		do {
			read = port.readSerialPort(buffer, 255);
		}
		while( read == 0);
		printf("Received %d characters\n", read);
		printf("Received: %s\n", buffer);
	}
	return 0;
}
