#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
    printf("hello (pid:%d)\n", (int) getpid());
    int fd = open("ex2_hw.txt", O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("child (pid:%d) (fd:%d)\n", (int) getpid(), fd);
        char* data = "Child\n";
        int bytes_to_write = strlen(data);
        int bytes_written = write(fd, data, bytes_to_write);
        if (bytes_written != bytes_to_write) {
            perror("write child");
            exit(1);
        }
        close(fd);
    } else {
        printf("parent of %d (pid:%d) (fd:%d)\n", rc, (int) getpid(), fd);
        char* data = "parent\n";
        int bytes_to_write = strlen(data);
        int bytes_written = write(fd, data, bytes_to_write);
        if (bytes_written != bytes_to_write) {
            perror("write parent");
            exit(1);
        }
        close(fd);
    }
    return 0;
}