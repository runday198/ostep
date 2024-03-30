#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    char *src = "hello";
    char *dst = (char *) malloc(strlen(src)); 
    strcpy(dst, src); 
}