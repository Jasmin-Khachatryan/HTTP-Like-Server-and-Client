#include "utils.h"
#include <unistd.h>

int read_line(int fd, char *buffer, int size) {
    int i = 0;
    char c;
    while (i < size - 1) {
        int n = read(fd, &c, 1);
        if (n <= 0) break;
        buffer[i++] = c;
        if (c == '\n') break;
    }
    buffer[i] = '\0';
    return i;
}

