#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>



void error_y_exit (char *str) {
  perror (str);
  exit (EXIT_FAILURE);
}


void Usage () {
  char buffer[256];
  sprintf (buffer, "USAGE: userprocs username\n");
  write (1, buffer, strlen (buffer));
  exit (EXIT_FAILURE);
}




int main (int argc, char *argv[]) {

  int fd_paresbin;
  int numero_pares;
  char buffer[256];

  fd_paresbin = open ("pares.bin", O_RDONLY, 0);
  if ((fd_paresbin == -1) && (errno == ENOENT))
    error_y_exit ("el fichero pares.bin no existe");
  if ((fd_paresbin == -1) && (errno != ENOENT))
    error_y_exit ("error general open");

  numero_pares = lseek (fd_paresbin, 0, SEEK_END) / sizeof (int);
  sprintf (buffer, "En pares.bin hay %d números pares\n", numero_pares);
  write (1, buffer, strlen (buffer));
}
