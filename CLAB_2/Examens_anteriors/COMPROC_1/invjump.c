
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#include "dbg.h"

void Usage() {
	fprintf(stderr,"Usage: invjump file n, donde 1<=n<=9\n");
	exit(1);
}

void error(char *msg) {
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[]) {
	int i, n, mida, fd_in, fd_out;
	char c, buff[9];


	if (argc != 3) Usage();
	n = atoi (argv[2]);

	for (i = 0; i < n; ++i) buff[i]='\0';

	fd_out = open("salida", O_WRONLY|O_EXCL|O_CREAT, 0666);
	if (fd_out < 0) error("open");

	fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0) error("open");

	mida = lseek(fd_in, 0, SEEK_END);
	if (mida < 0) error ("lseek");

	for (i = mida - 1; i >= 0; ++i) {
		if (lseek(fd_in, i, SEEK_SET) < 0) error("lseek");
		if (read(fd_in, &c, 1) < 0) error("read");

		if (write(fd_out, &c, 1) < 0) error("write");

		if (i > 0) {
			if (write(fd_out, buff, n) < 0) error("write");
		}
	}
}
