#include <stdio.h>
#include <string.h>
#include <errno.h>

extern "C" {
#include <wiringPi.h>
#include <wiringSerial.h>
}

int main ()
{
  int fd ;
  int count ;
  unsigned int nextTime = 0 ;

  if ((fd = serialOpen ("/dev/ttyUSB0", 115200)) < 0)
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }
  delay(3500);
  
	//serialFlush(fd);

  if (wiringPiSetup () == -1)
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }
  
  serialFlush (fd);

  
	  //nextTime = millis () + 3000 ;

  for (;;)
  {
    //if (millis () > nextTime)
    {
      printf ("\nOut: %3d: ", count) ;
      fflush (stdout) ;
      serialPuts(fd, "5*1000/0/0!");
      //serialPutchar (fd, count) ;
      nextTime += 300 ;
      ++count ;
      nextTime = millis();
    }

    //delay (1200) ;
    
    auto dataAvail = 0;
    //do {
    while (dataAvail == 0 && millis() < nextTime + 10000) {
		dataAvail = serialDataAvail (fd); }
		if ( dataAvail == -1 ) {
			printf (" Bad port\n ");
			fflush (stdout) ;
		}
		else if ( dataAvail != 0 ) {
			printf (" avail %d \n ", dataAvail);
			fflush (stdout) ;
		}
	//}	while(dataAvail == 0);
	
	int ct = 0;

    while (ct < dataAvail)
    {
		ct++;
	  int chRead = serialGetchar (fd);
	  if ( chRead != -1 ) {
		  
			printf (" -> %c\n", (char)chRead);
		  //break;
	  }
      fflush (stdout) ;
    }
    if ( ct != 0 ) {
			
    printf (" Count %3d\n", ct);
	}
  }

  printf ("\n") ;
  return 0 ;
}
