
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

#include "dbg.h"

void ras_alarm(int signo)
{
	fprintf(stderr,"tick\n");
}

void Usage()
{
	fprintf(stderr,"Usage: reader_np \n");
	exit(1);
}

#define NP "pipe-np"

int main(int argc, char *argv[])
{
	int fd, fd_out;

	if (argc!=1) Usage();

	if (mkfifo(NP, 0600) < 0) {
		if (errno == EEXIST)
			fprintf(stderr,"Named pipe ja existeix\n");
		else
			panic("creant NP");
	}
	
	fd = open(NP, O_RDONLY);
	if (fd < 0) panic("open");

	switch(fork()) {
		case -1 : panic("fork");

		case 0:
			if (dup2(fd, 0) < 0) panic("dup2");
			fd_out = open("salida", O_WRONLY|O_EXCL|O_CREAT, 0600);
			if (fd_out<0) panic("open");
			if (dup2(fd_out, 1) < 0) panic("dup2");
			if (close(fd_out) < 0) panic("close");

			execlp("sed", "sed", "-e", "y/e/3/", "-e", "y/i/1/", "-e", "y/o/0/", NULL);
			panic("exec");
	}

	wait(NULL);
}

