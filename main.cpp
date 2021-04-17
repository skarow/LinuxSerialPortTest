#include "SerialPortLinux.h"

int main()
{
	SerialPort port("/dev/ttyUSB0");
	
	char* str = "5*1000/0/0!1";
    char buffer[15];
	
	for ( int i = 0; i < 4; ++ i) 
    {
		port.writeSerialPort(str, 10);
		
		int read = 0;
		do {
			read = port.readSerialPort(buffer, 15);
		}
		while( read == 0);
		printf("Received %d characters\n", read);
		printf("Received: %s\n", buffer);
	}
	return 0;
}
