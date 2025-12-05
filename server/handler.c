#include "handler.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER 1024

void *handle_client(void *arg) {
    int client_fd = *(int *)arg;
    free(arg);

    char buffer[BUFFER];
    int n = read(client_fd, buffer, sizeof(buffer)-1);
    if (n <= 0) { 
        close(client_fd);
        return NULL;
    }

    buffer[n] = '\0';
    printf("Received:\n%s\n", buffer);

    char method[16], resource[256], version[16];
    sscanf(buffer, "%15s %255s %15s", method, resource, version);

    int body_size = 0;
    char *body_ptr = strstr(buffer, "Body-Size:");

    if (body_ptr) {
        sscanf(body_ptr, "Body-Size: %d", &body_size);
    }

    char *msg_body = strstr(buffer, "\n\n");
    if (msg_body) {
        msg_body += 2;
    }

    char response[BUFFER];

    if (strcmp(method, "GET") == 0) {
        char filepath[512];
        snprintf(filepath, sizeof(filepath), "server/files/%s", resource+1);

        FILE *f = fopen(filepath, "r");
        if (f) {
            char content[BUFFER];
            int len = fread(content, 1, sizeof(content)-1, f);
            content[len] = '\0';
            fclose(f);

            snprintf(response, sizeof(response),
                     "CHLP/1.0 200 OK\nBody-Size: %d\n\n%s", len, content);
        } else {
            snprintf(response, sizeof(response),
                     "CHLP/1.0 404 Not Found\nBody-Size:0\n\n");
        }
    } else if (strcmp(method, "POST") == 0) {
        char savepath[512];
        snprintf(savepath, sizeof(savepath), "files/%s", resource+1);
        FILE *f = fopen(savepath, "w");
        if (f) {
            fwrite(msg_body, 1, body_size, f);
            fclose(f);
        }
        snprintf(response, sizeof(response), "CHLP/1.0 200 OK\nBody-Size:0\n\n");
    } else if (strcmp(method, "ECHO") == 0) {
        snprintf(response, sizeof(response), "CHLP/1.0 200 OK\nBody-Size: %d\n\n%s", body_size, msg_body);
    } else {
        snprintf(response, sizeof(response), "CHLP/1.0 400 Bad Request\nBody-Size:0\n\n");
    }

    write(client_fd, response, strlen(response));
    close(client_fd);
    return NULL;
}

