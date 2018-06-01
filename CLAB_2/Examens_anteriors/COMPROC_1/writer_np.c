
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
	fprintf(stderr,"Usage: writer_np string\n");
	exit(1);
}

#define NP "pipe-np"

int main(int argc, char *argv[])
{
	int fd, i;
	struct sigaction ras;
	sigset_t mask, mask_bl_sigalarm;

	if (argc!=2) Usage();

	if (mkfifo(NP, 0600) < 0) {
		if (errno == EEXIST)
			fprintf(stderr,"Named pipe ja existeix\n");
		else
			panic("creant NP");
	}
	
	fd = open(NP, O_WRONLY);
	if (fd < 0) panic("open");

	ras.sa_handler = ras_alarm;
	ras.sa_flags = 0;
	sigemptyset(&ras.sa_mask);
	if (sigaction(SIGALRM, &ras, NULL) < 0) panic("sigaction");

	sigemptyset(&mask_bl_sigalarm); sigaddset(&mask_bl_sigalarm, SIGALRM);
	sigprocmask(SIG_BLOCK, &mask_bl_sigalarm, NULL);
	
	sigfillset(&mask); sigdelset(&mask, SIGALRM);
	
	for (i=0; i<strlen(argv[1]); i++) {
		// Esperar un segon
		alarm(1);
		sigsuspend(&mask);

		if (write(fd, &argv[1][i], 1) < 0) panic("write");
	}	
	if (close(fd) < 0) panic("close");
}

