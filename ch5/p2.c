#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    printf("hello (pid:%d)\n", (int) getpid());
    int i = 5;
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("child (pid:%d) (i:%d)\n", (int) getpid(), i);
        int rc1 = fork();
        if (rc1 < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (rc1 == 0) {
            printf("Child of child (pid:%d) (i:%d)\n", (int) getpid(), i);
        } else {
            sleep(1);
            printf("Child parent of %d (pid:%d) (i:%d)\n", rc1, (int) getpid(), i);   
        }
    } else {
        int rc_wait = wait(NULL);
        printf("parent of %d (rc_wait:%d) (pid:%d) (i:%d)\n", rc, rc_wait, (int) getpid(), i);
    }
    return 0;
}

