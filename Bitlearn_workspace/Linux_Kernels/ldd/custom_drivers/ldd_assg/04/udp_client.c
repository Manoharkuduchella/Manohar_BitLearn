/* udp_client.c */

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
    struct sockaddr_in server_addr;
    socklen_t server_len;
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

    inet_pton(AF_INET,
              "127.0.0.1",
              &server_addr.sin_addr);

    server_len = sizeof(server_addr);

    /* Send data */
    strcpy(buffer, "Hello from UDP client");

    sendto(sockfd,
           buffer,
           strlen(buffer) + 1,
           0,
           (struct sockaddr *)&server_addr,
           server_len);

    /* Receive reply */
    memset(buffer, 0, sizeof(buffer));

    recvfrom(sockfd,
             buffer,
             sizeof(buffer),
             0,
             NULL,
             NULL);

    printf("Received from server: %s\n", buffer);

    close(sockfd);

    return 0;
}
