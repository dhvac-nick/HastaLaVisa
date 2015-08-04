#include <stdio.h>
#include <termios.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <string.h>
#include <errno.h>


static int fd = 0;
char psResponse[10];
int iIn = 0;
int iOut = 0;
char CurrentPath[80];

char DeltaServerIP[80];
int main(void)
{
	/*
	while(1)
	{
		fd = open("/dev/ttyO1", O_RDWR | O_NOCTTY | O_NONBLOCK);
		iIn = read(fd, psResponse, 1);
		printf("%d\n", iIn);	
		sleep(2);
	}
	*/
		printf("Test 1 \n");
	
		strcat(CurrentPath,"/tmp/ttt_system");
		/* Open IP File */
		FILE	*fr;
		fr = fopen(CurrentPath,"r");
		if (fr == NULL){
			printf("File can not found.\n");
			exit(0);
		}
		fscanf(fr,"id\t%s",&DeltaServerIP);
		printf("DeltaServerIP = %s\n",DeltaServerIP);	
	exit(0);
	

}




