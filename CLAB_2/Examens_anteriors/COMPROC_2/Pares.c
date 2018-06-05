#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void error (char *msg) {
    perror(msg);
    exit(1);
}

void Usage() {
    char buff[58];
    sprintf(buff,"Usage: parametres no correctes\n");
    write(1,buff,strlen(buff));
}

int main(int argc, char const *argv[]) {

    if (argc != 1)
        Usage();

    int ret;
    int num;
    char buff[256];
    while ((ret = read(0,&num, sizeof(num))) > 0) {
        if (num%2 == 0) {
            sprintf(buff,"%d\n",num);
            if (write(1,buff,strlen(buff)) < 0)
                error("write");
        }
    }
    if (ret  < 0) error("read");
    return 0;
}
