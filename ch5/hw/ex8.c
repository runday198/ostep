#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        fprintf(stderr, "pipe");
        exit(1);
    }
    printf("hello (pid:%d)\n", (int) getpid());

    int rc1 = fork();
    if (rc1 < 0) { 
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc1 == 0) {
        int status;
        close(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);

        int rc_wait_child = waitpid((pid_t) -1, &status, 0);
        printf("rc_wait_child: %d\n", rc_wait_child);
    } else {
        int rc2 = fork();

        if (rc2 < 0) {
            fprintf(stderr, "fork\n");
            exit(1);
        } else if (rc2 == 0) {
            close(STDIN_FILENO);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
            close(pipefd[1]);

            char buffer[BUFSIZ];
            int bytes_read = read(0, buffer, BUFSIZ);
            buffer[bytes_read] = '\0';

            printf("Child read: %s", buffer);
        } else {
            while(wait(NULL) > 0);
        }
    }
    return 0;
}
