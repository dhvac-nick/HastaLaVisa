#include <stdio.h>
#include <termios.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <errno.h>

#define BAUDRATE B57600
#define LINESPEED B57600


static int fd = 0;
char psResponse[30];
int iIn = 0;
int iOut = 0;
int n_wrtn , n_read, ret_f,bytes ;
char buf[100];
struct termios oldtio,newtio;

int main (void)
{
   int fd,                                // Handle for POSIX I/O
       i;
   struct termios otios, ntios;           // Terminal I/O structures
   char buf[255];                         // Buffer

   // Open /dev/ttyS1 (COM2 port of DNP/EVA2)...

   fd= open ("/dev/ttyO5", O_RDWR | O_NOCTTY );
   if (fd < 0) {
      perror ("/dev/ttyO5");
      exit (-1);
   }

   // Save current /dev/ttyS1 setup

   tcgetattr (fd, &otios);

   // Define new setup for /dev/ttyS1...

   bzero (&ntios, sizeof (ntios));
   ntios.c_cflag= LINESPEED | CRTSCTS | CS8 | CLOCAL | CREAD;
   ntios.c_cc[VTIME]= 0;      // No timeouts
   ntios.c_cc[VMIN]= 1;       // Wait for one char (and not more)

   // Write new setup to /dev/ttyS1...

   tcflush (fd, TCIFLUSH);
   tcsetattr (fd, TCSANOW, &ntios);

   // Send sign-in message to terminal program on /dev/ttyS1

   sprintf (buf, "Test Program for DNP/EVA2 COM2 (/dev/ttyO1)\n\r\n\r");
   write (fd, buf, strlen (buf));

   // Wait for char from /dev/ttyS1. Display all char's.

   while (1) {
      i= read (fd, buf, 255);              // Receive from /dev/ttyS1
      buf[i]= 0;
      printf ("%s", buf);
      fflush (stdout);
      write (fd, buf, strlen (buf));       // Send echo over /dev/ttyS1

      // Make new line if necessary

      if (buf[0] == '\r') {
         printf ("\n");
         sprintf (buf, "\n");
         write (fd, buf, strlen (buf));
      }
   }

   // Restore old setup for /dev/ttyS1...

   tcsetattr (fd, TCSANOW, &otios);
   exit (1);
}




