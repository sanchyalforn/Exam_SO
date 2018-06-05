#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>



void
error_y_exit (char *str)
{
  perror (str);
  exit (EXIT_FAILURE);
}


void
Usage ()
{
  char buffer[256];
  sprintf (buffer, "USAGE: userprocs username\n");
  write (1, buffer, strlen (buffer));
  exit (EXIT_FAILURE);
}




int
main (int argc, char *argv[])
{

  int pares2wc[2];
  int fd_entrada, fd_wc2padre;
  int ret;
  char wcbuffer[256];
  char buffer[256];


  if (argc != 2)
    Usage ();

  pipe (pares2wc);



  switch (fork ())		//fork para mutar a ps
    {
    case -1:
      error_y_exit ("Fork para ps");
      break;
    case 0:
      dup2 (pares2wc[1], 1);
      close (pares2wc[1]);	//redirecció Salida Estandar a pipe. Cierre canal duplicado.

      close (0);
      fd_entrada = open (argv[1], O_RDONLY, 0);	//redirección del fichero den entrada como entrada estandard
	close (pares2wc[0]);	//cierro canales de pipe que no uso

      execlp ("./pares", "pares", (char *) NULL);
      error_y_exit ("Mutación a pares");
      break;

    }

  switch (fork ())		//fork para mutar a grep
    {
    case -1:
      error_y_exit ("Fork para grep");
      break;
    case 0:
      dup2 (pares2wc[0], 0);
      close (pares2wc[0]);	//redirecció entrada Estandar a pipe. Cierre canal duplicado.

      close (1);		// redirección a la pipe con nombre
      fd_wc2padre = open ("wc2padre", O_WRONLY, 0);	//bloqueante

      close (pares2wc[1]);	//cierro canales de pipe que no uso

      execlp ("wc", "wc", "-l", (char *) NULL);
      error_y_exit ("Mutación a wc");
      break;

    }

///PADRE
//Cierro los canales de pipe que no uso
  close (pares2wc[0]);
  close (pares2wc[1]);

  fd_wc2padre = open ("wc2padre", O_RDONLY, 0);	//abre la named-pipe. Hay bloqueo

  while ((ret = read (fd_wc2padre, wcbuffer, 256)) > 0)	{ //la lectura se bloquea hasta que wc acaba
      wcbuffer[ret - 1] = '\0';
      sprintf (buffer,
	       "El fichero %s contiene %s pares\n", argv[1], wcbuffer);
      write (1, buffer, strlen (buffer));
    }

  close (fd_wc2padre);
  while (waitpid (-1, NULL, 0) > 0);


}
