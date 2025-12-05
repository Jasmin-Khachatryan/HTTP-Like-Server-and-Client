#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER 1024

int main() {
    int sock;
    struct sockaddr_in addr;
    char buffer[BUFFER];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) { 
        perror("socket"); exit(1); 
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("connect"); exit(1);
    }

    int choice;
    printf("Choose request type:\n1. GET\n2. POST\n3. ECHO\n> ");
    scanf("%d", &choice);
    getchar();

    char request[BUFFER];
    char resource[256], body[512];

    switch (choice) {
        case 1: // GET
            printf("Enter file to GET (e.g., index.txt): ");
            scanf("%255s", resource);
            snprintf(request, sizeof(request),
                     "GET /%s CHLP/1.0\nBody-Size:0\n\n", resource);
            break;

        case 2: // POST
            printf("Enter filename to save (e.g., test.txt): ");
            scanf("%255s", resource);
            getchar();
            printf("Enter message body: ");
            fgets(body, sizeof(body), stdin);
            int len = strlen(body);

            if (body[len-1] == '\n') { 
                body[len-1] = '\0'; len--;
            }
            snprintf(request, sizeof(request),
                     "POST /%s CHLP/1.0\nBody-Size:%d\n\n%s", resource, len, body);
            break;

        case 3: // ECHO
            printf("Enter message to echo: ");
            fgets(body, sizeof(body), stdin);
            int echo_len = strlen(body);

            if (body[echo_len-1] == '\n') { 
                body[echo_len-1] = '\0'; echo_len--;
            }

            snprintf(request, sizeof(request),
                     "ECHO /echo CHLP/1.0\nBody-Size:%d\n\n%s", echo_len, body);
            break;

        default:
            printf("Invalid choice\n");
            close(sock);
            return 0;
    }

    write(sock, request, strlen(request));

    int n = read(sock, buffer, sizeof(buffer)-1);
    if (n > 0) {
        buffer[n] = '\0';
        printf("\nResponse:\n%s\n", buffer);
    }

    close(sock);
    return 0;
}


