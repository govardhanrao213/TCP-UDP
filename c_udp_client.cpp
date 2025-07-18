#include <stdio.h>        // For printf(), perror()
#include <stdlib.h>     // For exit()
#include <string.h>    // For memset() 
#include <unistd.h>   // For close()
#include <arpa/inet.h>  // For socket functions

#define SERVER_IP "127.0.0.1"       // Update to your server's IP address
#define SERVER_PORT 12345       // Update to your server's port
#define BUFFER_SIZE 1024         // Buffer size for receiving data  

int main() {
    int sockfd;         // Socket file descriptor   
    char buffer[BUFFER_SIZE];           // Buffer for receiving data
    struct sockaddr_in server_addr; // Server address structure     

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);         // AF_INET: IPv4, SOCK_DGRAM: UDP, 0: IP protocol
                                          
    if (sockfd < 0) {
        perror("Socket creation failed");       
        return 1;       // Handle socket creation failure
    }

    memset(&server_addr, 0, sizeof(server_addr));   // Clear server address structure          
    server_addr.sin_family = AF_INET;   // IPv4
    server_addr.sin_port = htons(SERVER_PORT);  // Port number
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);       // Convert IP address from text to binary form

    // Send message to server
    const char *message = "Hello from C UDP client!";                           
    sendto(sockfd, message, strlen(message), 0,                 
           (const struct sockaddr *)&server_addr, sizeof(server_addr));         // Send data to server                       
    printf("Message sent to server\n");                         

    // Receive reply from server
    socklen_t addr_len = sizeof(server_addr);                                   
    ssize_t n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,                
                         (struct sockaddr *)&server_addr, &addr_len);       // Receive data from server        
    buffer[n] = '\0';       // Null-terminate the received string

    printf("Server replied: %s\n", buffer);                                     

    close(sockfd);      // Close the socket
    return 0;                // Return success       
}
