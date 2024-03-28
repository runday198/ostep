#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>

int main() {
    cpu_set_t cpu_mask;
    CPU_ZERO(&cpu_mask);
    CPU_SET(1, &cpu_mask);

    if (sched_setaffinity(0, sizeof(cpu_mask), &cpu_mask) != 0) {
        fprintf(stderr, "setaffinity");
        exit(1);
    }

    int pipefd1[2];

    if (pipe(pipefd1) == -1) {
        fprintf(stderr, "pipe");
        exit(1);
    }

    int pipefd2[2];

    if (pipe(pipefd2) == -1) {
        fprintf(stderr, "pipe2");
        exit(1);
    }

    int rc1 = fork();
    if (rc1 < 0) {
        fprintf(stderr, "fork1");
        exit(1);
    } else if(rc1 == 0) {
        dup2(pipefd1[1], STDOUT_FILENO);
        close(pipefd1[0]);
        dup2(pipefd2[0], STDIN_FILENO);
        close(pipefd2[1]);

        char buffer[BUFSIZ];
        for (int i = 0; i < 2; i++) {
            printf("child 1: %d\n", 10);

            int bytes_read = read(0, buffer, BUFSIZ);
            buffer[bytes_read] = '\0';
        }
        close(pipefd1[1]);
        close(pipefd2[0]);
    } else {
        int rc2 = fork();

        if (rc2 < 0) {
            fprintf(stderr, "fork");
            exit(1);
        } else if (rc2 == 0) {
            dup2(pipefd1[0], STDIN_FILENO);
            close(pipefd1[1]);
            dup2(pipefd2[1], STDOUT_FILENO);
            close(pipefd2[0]);

            char buffer[BUFSIZ];

            for (int i = 0; i < 1; i++) {
                int bytes_read = read(0, buffer, BUFSIZ);
                buffer[bytes_read] = '\0';

                printf("Child 2 read: %s\n", buffer);
            }

            close(pipefd1[0]);
            close(pipefd2[1]);
            
        } else {
            close(pipefd1[0]);
            close(pipefd1[1]);
            close(pipefd2[0]);
            close(pipefd2[1]);
            
            while(wait(NULL) > 0);
        } 
    }
}