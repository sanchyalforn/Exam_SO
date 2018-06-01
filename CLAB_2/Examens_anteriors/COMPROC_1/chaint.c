
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#include "dbg.h"

void Usage()
{
	fprintf(stderr,"Usage: chaint n, donde 1<=n<=9\n");
	exit(1);
}

int main(int argc, char *argv[])
{
	int n, x, fd;
	int p1[2], p2[2];
	char s[80];

	if (argc != 2) Usage();
	n = atoi(argv[1]);

	if ((n<1) || (n>9)) Usage();

	if (pipe(p1)<0) panic("pipe");
	if (pipe(p2)<0) panic("pipe");

	switch(fork()) {
		case -1 : panic("fork");
		case 0: /* H1 */
			if (close(p1[0]) < 0) panic("close");
			if (close(p2[0]) < 0) panic("close");
			if (close(p2[1]) < 0) panic("close");

			if (write(p1[1], &n, sizeof(int))<0) 
				panic("write");

			if (close(p1[1]) < 0) panic("close");
			exit(0);			
	}

	switch(fork()) {
		case -1 : panic("fork");
		case 0: /* H2 */
			if (close(p1[1]) < 0) panic("close");
			if (close(p2[0]) < 0) panic("close");

			if (read(p1[0], &x, sizeof(int)) < 0)
				panic("read");
			x = x*x;
			if (write(p2[1], &x, sizeof(int))<0) 
				panic("write");

			if (close(p1[0]) < 0) panic("close");
			if (close(p2[1]) < 0) panic("close");
			exit(0);			
	}
	switch(fork()) {
		case -1 : panic("fork");
		case 0: /* H3 */
			if (close(p1[0]) < 0) panic("close");
			if (close(p1[1]) < 0) panic("close");
			if (close(p2[1]) < 0) panic("close");

			if (read(p2[0], &x, sizeof(int)) < 0)
				panic("read");

			fd = open("salida", O_WRONLY|O_TRUNC|O_CREAT, 0664);
			if (fd<0) panic("open");

			sprintf(s, "%d\n", x);

			if (write(fd, s, strlen(s)) < 0) panic("write");

			if (close(fd)<0) panic("close");
			if (close(p2[0]) < 0) panic("close");
			exit(0);			
	}

	if (close(p1[0]) < 0) panic("close");
	if (close(p1[1]) < 0) panic("close");
	if (close(p2[0]) < 0) panic("close");
	if (close(p2[1]) < 0) panic("close");

	if (wait(NULL) < 0) panic("wait");
	if (wait(NULL) < 0) panic("wait");
	if (wait(NULL) < 0) panic("wait");
}
