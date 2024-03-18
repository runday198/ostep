#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    int fd = open("/tmp/file", O_WRONLY | O_CREAT | O_TRUNC);
    assert(fd > -1);
    int rc = write(fd, "hello world\n", 13);
    asserc(rc == 13);
    close(fd);
    return 0;
}
