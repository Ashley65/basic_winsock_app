//
// Created by NIgel work on 14/11/2023.
//

#ifndef NETWORK_TCP_CLIENT_H
#define NETWORK_TCP_CLIENT_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib") //Winsock Library
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

class TCP_client {
private:
    int socket_desc{};
    struct sockaddr_in server{};
    char server_reply[2000]{};
    int iResult{};
    SOCKET ConnectSocket = INVALID_SOCKET;
    int recvbuflen = DEFAULT_BUFLEN;

public:
    TCP_client();
    ~TCP_client();

    

    //Connect to remote server
    int connect();
    struct addrinfo *result = nullptr, *ptr =nullptr, hints{};



    char recvbuf[DEFAULT_BUFLEN]{};



    //Send some data
    int send(const char *message);

    //Receive a reply from the server
    int receive() ;

    //Close the socket
    void close();

    //for error checking'


    static void write(int sock, char message[2000], size_t strlen);

};


#endif //NETWORK_TCP_CLIENT_H
