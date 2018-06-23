#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <winsock.h>
#include <ctime>
// Required for Linux
//#include <sys/socket.h>
//#include <sys/types.h>
//#include <netinet/in.h>

#define TIMEOUT 5

int main() {

    // timer
    clock_t startTime = clock(); // start time
    double secondsPassed;
    
    char* dt;

    char server_message[256];
    char client_message[256];
    

    // create the server socket
    int server_socket = INVALID_SOCKET;
    int client_socket = INVALID_SOCKET;
    WSADATA wsaData;
    int iResult, read_size;

    // initialize winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(iResult != 0) {
        printf("WinSock failed to initialize!");
        return 1;
    }

    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(9002);

    // bind the socket to our specified IP and port
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    // listen for connections
    iResult = listen(server_socket, 5);
    if(iResult == SOCKET_ERROR) {
        printf("listen failed.");
    }

    time_t now = time(0);
    dt = ctime(&now);
    printf("TCP/IP Server\nCurrent time is: %s", dt);
    printf("Listening...\n");

    // server is always listening for connections
    while(client_socket = accept(server_socket, NULL, NULL)) {

        if(client_socket < 0) {
            printf("Connection error.");
        }

        printf("Connected to client!\n");

        // Listen for response from client
        while((read_size = recv(client_socket, client_message, sizeof(client_message), 0)) > 0) {

            // print client message
            printf("\nClient says: %s", client_message);
            
        }

        printf("\nListening...");
    }

    // close the socket
    close(server_socket);


    return 0;
}