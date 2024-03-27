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
        int status;
        
        int rc_wait_child = waitpid((pid_t) -1, &status, 0);
        printf("rc_wait_child: %d\n", rc_wait_child);
    } else {
        int status;
        int rc_wait = waitpid(0, &status, 0); 
        printf("rc_wait: %d\n", rc_wait);
    }
    return 0;
}
