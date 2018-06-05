#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

void error_y_exit (char *msg) {
  perror (msg);
  exit (1);
}

void usage () {
  char msg[256];

  sprintf (msg, "Usage: pares\n");
  write (2, msg, strlen (msg));
  exit (1);
}

int main (int argc, char *argv[]) {
  int f, value, ret, fd_fichero;
  char buffer[256];
  if (argc != 1)
    usage ();

  fd_fichero = open ("pares.bin", O_WRONLY | O_CREAT | O_EXCL, 0664);
  if (fd_fichero == -1) {

      if (errno == EEXIST) {
    	  sprintf (buffer,"El fichero pares.bin ya existe y será reescrito\n");
    	  write (2, buffer, strlen (buffer));
    	  if ((fd_fichero = open ("pares.bin", O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0)
    	    error_y_exit ("open pares.bin");
	  }
      else
	     error_y_exit ("creat pares.bin");
  }


  ret = read (0, &value, sizeof (value));
  while (ret > 0)
    {
      if ((value % 2) == 0)
	{
	  sprintf (buffer, "%d\n", value);
	  if (write (1, buffer, strlen (buffer)) < 0)
	    error_y_exit ("write");
	  if (write (fd_fichero, &value, sizeof (int)) < 0)
	    error_y_exit ("write");
	}
      ret = read (0, &value, sizeof (value));
    }
  if (ret < 0)
    error_y_exit ("read");

}
