#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
#include <pthread.h> 
#include <fcntl.h>  /* File Control Definitions          */
#include <termios.h>/* POSIX Terminal Control Definitions*/
#include <sys/ioctl.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>

#include <time.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

int main()
{
    struct termios o;
    int fd1;
    fd1=open("/dev/ttyS2", O_RDWR | O_NOCTTY | O_SYNC);  if(fd1==1)
	printf("\n Error! in openning ttyS1\n");
	else
	printf("ttyS1 Opened Successfully\n");

	// Trying to set correct options here
	
	tcgetattr(fd1,&o);
	cfsetispeed(&o,B9600);
	cfsetospeed(&o,B9600);
	o.c_cflag &= ~ PARENB;
	// o.c_cflag &= ~ PARODD;

	o.c_cflag &= ~CSTOPB;o.c_cflag &= ~CSIZE;o.c_cflag |= CS8;

	o.c_cflag &= ~CRTSCTS;

	o.c_cflag |= CREAD | CLOCAL;

	o.c_iflag &= ~(IXON | IXOFF | IXANY );

	o.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL );

	o.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

	o.c_oflag&=~OPOST;
	o.c_cc[VMIN] = 1; //to prevent delay in read();
	o.c_cc[VTIME] =1;
	tcsetattr(fd1, TCSANOW, &o);
	tcflush(fd1, TCIFLUSH);
  
  int rd;
  char buff[255];
  rd = read(fd1,buff,255);
  for (int i=0; i<255; i++)
  {
    printf("%c",buff[i]);
  }

  

}
