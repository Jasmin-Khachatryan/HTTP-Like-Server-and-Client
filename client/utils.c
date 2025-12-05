#include <stdio.h>
#include <unistd.h>
#include <string.h>

void send_request(int sock, const char *request) {
    write(sock, request, strlen(request));
}

