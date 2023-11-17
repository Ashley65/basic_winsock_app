//
// Created by NIgel work on 10/11/2023.
//

#ifndef NETWORK_TCP_SERVER_H
#define NETWORK_TCP_SERVER_H

#include <iostream>
#include <map>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib") //Winsock Library
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

struct sockaddr_in;

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

class TCP_server {

private:
    int c{}, read_size{};
    SOCKET socket_desc = INVALID_SOCKET;
    struct sockaddr_in server{}, client{};
    char client_message[2000]{};

public:
    TCP_server();
    ~TCP_server();

    struct addrinfo *result = nullptr, *ptr =nullptr, hints{};

    //Creates a temporary socket object for accepting connections from clients
    SOCKET client_socket{};




    //Socket to listen for incoming connections
    SOCKET listen() const;

    //Accept and incoming connection
    SOCKET accept();

     //Receive a message from a client
     int receive();


    //Send a message to the client
    int send(const char *message);

    //for error checking
    int iResult{};

    //Close the socket
    void close();

    // table to keep track of clients socket
    std::map<int, SOCKET> client_sockets;


    static void write(int sock, char message[2000], size_t strlen);
};



#endif //NETWORK_TCP_SERVER_H
