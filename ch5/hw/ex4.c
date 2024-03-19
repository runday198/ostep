#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[]) {
    printf("hello (pid:%d)\n", (int) getpid());

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        char* myargs[2];
        myargs[0] = strdup("/bin/ls");
        myargs[1] = NULL;
        execlp(myargs[0], myargs[1]);
    } else {
        wait(NULL);
    }
    return 0;
}
