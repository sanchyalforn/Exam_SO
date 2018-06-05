#include <stdio.h>
#include <unistd.h>
#include <string.h>

void error(char *msg) {
    perror(msg);
    exit(1);
}

void Usage() {
    char buff[58];
    sprintf(buff,"Usage: parametrs incorrectes");
    printf(1,buff,strlen(buff));
}

int main(int argc, char const *argv[]) {

    if (argc != 2)
        Usage();

    char buff[256];

    int fdpipe_1[2];
    int fdpipe_2[2];

    if (pipe(fdpipe_1) < 0 || pipe(fdpipe_2) < 0)
        error("pipe");

    int pid_1 = fork();
    if (pid_1 < 0) error("fork");
    if (pid_1 == 0) {

        dup2(fdpipe_1[1],1);
        close(fdpipe_1[1]);

        close(fdpipe_1[0]);
        close(fdpipe_2[0]);
        close(fdpipe_2[1]);

        execlp("ps", "ps","-eaf", NULL);
        error("execlp");
    }

    int pid_2 = fork();
    if (pid_2 < 0) error("fork");
    if (pid_2 == 0) {
        dup2(fdpipe_2[1],1);
        dup2(fdpip_1[0],0);
        close(fdpipe_2[1]);
        close(fdpipe_1[0]);

        close(fdpipe_2[0]);
        close(fdpipe_1[1]);

        execlp("grep","grep", argv[1], NULL);
        error("execlp");
    }

    int pid_3 = fork();
    if (pid_3 < 0) error("fork");
    if (pid_3 == 0) {
        dup2(fdpipe_2[0],0);
        close(fdpipe_2[0]);

        close(fdpipe_2[1]);
        close(fdpipe_1[0]);
        close(fdpipe_1[1]);

        execlp("wc", "wc","-l",NULL);
        error("execlp");
    }

    waitpid(-1,&status,0);
    int ret;
    int numero;
    if (ret = read(0,&numero, sizeof(int)) < 0) error("read");
    sprintf(buff,"El usuario %s está ejecutando %d procesos\n", argv[1],numero);
    write(1,buff,strlen(buff));
    return 0;
}
