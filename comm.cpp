#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int main(int argc, char* argv[]) 
{

	char * portName = "/dev/ttyUSB0";
    struct termios serial;
    char* str = "Hello";
    char buffer[10];

    printf("Opening %s\n", argv[1]);

    //int fd = open(argv[1], O_RDWR | O_NOCTTY | O_NDELAY);
    int fd = open(portName, O_RDWR | O_NOCTTY | O_NDELAY);

    if (fd == -1) {
        perror(argv[1]);
        return -1;
    }
    usleep(3500000);

    if (tcgetattr(fd, &serial) < 0) {
        perror("Getting configuration");
        return -1;
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
    
    for ( int i = 0; i < 4; ++ i) 
    {
		// Attempt to send and receive
		printf("Sending: %s\n", str);

		int wcount = write(fd, str, strlen(str));
		if (wcount < 0) {
			perror("Write");
			return -1;
		}
		else {
			printf("Sent %d characters\n", wcount);
		}
		bool read_input = false;
		while (! read_input ) {
			int rcount = read(fd, buffer, sizeof(buffer));
			if (rcount < 0) {
				perror("Read");
				return -1;
			}
			else if (rcount > 0 ){
				printf("Received %d characters\n", rcount);
				read_input = true;
			}
			else {
				continue;
			}

			buffer[rcount] = '\0';

			printf("Received: %s\n", buffer);
		}// while
	
	} // for

    close(fd);
    return 0;
}
