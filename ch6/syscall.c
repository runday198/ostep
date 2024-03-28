#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>

int main() {
    struct timeval start;
    struct timeval end;
    int fd = open("./blank.txt", O_RDONLY);
    char buffer[10];

    gettimeofday(&start, NULL);

    for (int i = 0; i < 100000; i++) {
        read(fd, buffer, 0);
    }

    gettimeofday(&end, NULL);

    printf("sec diff: %d\n", (int) (end.tv_sec - start.tv_sec));
    printf("micses diff: %.6f\n", (int) (end.tv_usec - start.tv_usec) / 100000.);

    close(fd);
}