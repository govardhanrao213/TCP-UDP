#include <stdio.h>      // For printf(), perror()
#include <stdlib.h>     // For exit()
#include <string.h>   // For memset()
#include <unistd.h>     // For close()
#include <arpa/inet.h>      // For socket functions

#define PORT 12345      // Update to your server's port
#define BUFFER_SIZE 1024    // Buffer size for receiving data

int main() {
    int sockfd;        // Socket file descriptor
    char buffer[BUFFER_SIZE];     // Buffer for receiving data
    struct sockaddr_in server_addr, client_addr;    // Server and client address structures
    socklen_t addr_len = sizeof(client_addr);           

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    // Parameters:
    // - AF_INET: IPv4
    // - SOCK_DGRAM: UDP
    // - 0: IP protocol, automatically chosen
    if (sockfd < 0) {
        perror("socket creation failed");   // Handle socket creation failure
        exit(EXIT_FAILURE);       // Handle socket creation failure
    }

    // Bind address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;       // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;   // Accept connections from any IP address
    server_addr.sin_port = htons(PORT);     // Port

    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");   // Handle bind failure
        close(sockfd);  // Close the socket before exiting
        exit(EXIT_FAILURE);        // Handle bind failure         
    }

    printf("UDP Server listening on port %d...\n", PORT);

    while (1) {
        ssize_t len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,
                               (struct sockaddr *)&client_addr, &addr_len);    // Receive data from client
        buffer[len] = '\0'; // Null-terminate the received string
        printf("Client: %s\n", buffer); // Print received message

        sendto(sockfd, "ACK", 3, 0, (struct sockaddr *)&client_addr, addr_len); // Send acknowledgment back to client
    }

    close(sockfd);  // Close the socket
    return 0;       // Return success
}
