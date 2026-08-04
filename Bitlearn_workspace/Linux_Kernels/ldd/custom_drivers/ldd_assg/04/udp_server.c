/* udp_server.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(void)
{
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    char buffer[BUFFER_SIZE];

    /* Create UDP socket */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    /* Configure server address */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    /* Bind socket */
    if (bind(sockfd,
            (struct sockaddr *)&server_addr,
            sizeof(server_addr)) < 0)
    {
        perror("bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("UDP Server listening on port %d...\n", PORT);

    client_len = sizeof(client_addr);

    /* Receive message */
    memset(buffer, 0, sizeof(buffer));
    recvfrom(sockfd,
             buffer,
             sizeof(buffer),
             0,
             (struct sockaddr *)&client_addr,
             &client_len);

    printf("Received from client: %s\n", buffer);

    /* Send reply */
    strcpy(buffer, "Hello from UDP server");

    sendto(sockfd,
           buffer,
           strlen(buffer) + 1,
           0,
           (struct sockaddr *)&client_addr,
           client_len);

    close(sockfd);

    return 0;
}
