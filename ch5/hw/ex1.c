#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    printf("hello (pid:%d)\n", (int) getpid());
    int x = 20;
    int* pX = &x;
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        sleep(1);
        *pX = 5;
        printf("child (pid:%d) (x:%d) (pX:%p)\n", (int) getpid(), x, pX);
    } else {
        *pX = 15;
        int rc_wait = wait(NULL);
        printf("parent of %d (wait:%d) (pid:%d) (x:%d) (pX:%p)\n", rc, rc_wait, (int) getpid(), x, pX);
    }
    return 0;
}