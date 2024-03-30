#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    char *arg = argv[1];
    int total_bytes = atoi(arg) * 1024 * 1024;

    printf("%d\n", (int) getpid());

    int* array = (int*)malloc(total_bytes);

    int num_elements = total_bytes / sizeof(int);

    while (1) {
        for (int i = 0; i < num_elements; i++) {
            array[i];
        }
    } 
}