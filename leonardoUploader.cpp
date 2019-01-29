#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <iostream>
#include <sys/ioctl.h>

using namespace std;

int fd;
int retSystem;
struct termios termAttr;

int main(int argc, char *argv[])
{
	//open serial
	fd = open(argv[1], O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1)
	{
		perror("open_port: Unable to open serial port\n");
		exit(1);
	}
	cout << "Open Serial...." << endl;

	//set baud to 1200 to reset Arduino Leonardo
	tcgetattr(fd,&termAttr);
	cfsetispeed(&termAttr,B1200);
	cfsetospeed(&termAttr,B1200);
	tcsetattr(fd,TCSANOW,&termAttr);

	int RTS_flag, DTR_flag;
	RTS_flag = TIOCM_RTS;
	DTR_flag = TIOCM_DTR;
	ioctl(fd,TIOCMBIS,&RTS_flag);//Set RTS pin
	ioctl(fd,TIOCMBIC,&DTR_flag);//Clear DTR pin

	close(fd);
	cout << "Reset Arduino Leonardo...." << endl;

	//delay 2 seconds after reseting
	sleep(2);

	//Upload firmware .hex
	char comport[32];
	strcpy(comport, "-P");
	strcat(comport,argv[1]);
	char hexfile[128];
	strcpy(hexfile, " -Uflash:w:");
	strcat(hexfile,argv[2]);
	char cmd[256];
	strcpy(cmd, "avrdude -pm32u4 -cavr109 -F -D ");
	strcat(cmd, comport);
	strcat(cmd,hexfile);
	//retSystem = system("avrdude -pm32u4 -cavr109 -D -P/dev/ttyACM0 -b57600 -Uflash:w:Blink.ino.hex");
	cout << "avrdude cmd :" << cmd << endl;
	retSystem = system(cmd);

	exit(0);
	return 0;
}
