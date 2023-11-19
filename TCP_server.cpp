//
// Created by NIgel work on 10/11/2023.
//

#include "TCP_server.h"
#include <iostream>

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

TCP_server::TCP_server() {
    WSADATA wsaData;

    //Initialise winsock
    std::cout << "Initialising Winsock..." << std::endl;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "Failed. Error Code : " << WSAGetLastError() << std::endl;
        exit(1);
    }
     std::cout << "Initialised." << std::endl;

    //Create a socket
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags= AI_PASSIVE;

    //Resolve the server address and port
    iResult = getaddrinfo(nullptr, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        std::cout << "getaddrinfo failed with error: " << iResult << std::endl;
        WSACleanup();
        exit(1);
    }
    std::cout << "getaddrinfo done" << std::endl;

    //Create a socket


    //Bind the socket to an address and port
    for (ptr = result; ptr != nullptr; ptr = ptr->ai_next) {
        socket_desc = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (socket_desc == INVALID_SOCKET) {
            std::cout << "socket failed with error: " << WSAGetLastError() << std::endl;
            WSACleanup();
            exit(1);
        }
        std::cout << "socket done" << std::endl;

        //Bind
        iResult = bind(socket_desc, ptr->ai_addr, (int) ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            std::cout << "bind failed with error: " << WSAGetLastError() << std::endl;
            closesocket(socket_desc);
            WSACleanup();
            exit(1);
        }
        std::cout << "bind done" << std::endl;
        // Free the addrinfo structure pointed to by result, because it is no longer needed.
        freeaddrinfo(result);
    }

}

TCP_server::~TCP_server() {

    closesocket(socket_desc);
    closesocket(client_socket);
    WSACleanup();

}

void TCP_server::write(int sock, char *message, size_t strlen) {
    //Send some data
    if (::send(sock, message, strlen, 0) < 0) {
        std::cout << "Send failed" << std::endl;
        exit(1);
    }
    std::cout << "Data send" << std::endl;

}

SOCKET TCP_server::listen() const {
    //Listen
    if (::listen(socket_desc, 3) == SOCKET_ERROR) {
        std::cout << "listen failed with error: " << WSAGetLastError() << std::endl;
        closesocket(socket_desc);
        WSACleanup();
        exit(1);
    }
    std::cout << "Waiting for incoming connections..." << std::endl;

    return socket_desc;
}

SOCKET TCP_server::accept() {

    std::cout << "accept process started" << std::endl;
    client_socket = INVALID_SOCKET;
    //Accept and incoming connection
    client_socket = ::accept(socket_desc, nullptr, nullptr);
    if (client_socket == INVALID_SOCKET) {
        std::cout << "accept failed with error: " << WSAGetLastError() << std::endl;
        closesocket(socket_desc);
        WSACleanup();
        exit(1);
    }
    std::cout << "Connection accepted" << std::endl;

    return client_socket;

}

int TCP_server::receive() {

    std::cout << "receive process started" <<std::endl;

    // increase the size of the message if needed
    char clientMessage[4096];

    //test check to see if the function is being called
    std::cout << "test check" << std::endl;

    // set timeout for recv function
    struct timeval timeout;
    timeout.tv_sec = 10; // 10 seconds
    timeout.tv_usec = 0; // Not initiating this can cause strange errors

    if (setsockopt(client_socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0) {
        std::cout << "setsockopt failed" <<WSAGetLastError() << std::endl;
        return 0;
    }

// receive a message from a client
    while (true){
        std::cout << "test check 2" << std::endl;

        int readSize = recv(client_socket, clientMessage, sizeof(clientMessage) , 0);
        if (readSize > 0) {
            std::cout << "Message received" << std::endl;
            std::cout << clientMessage << std::endl;
            return 1;
        } else if (readSize == 0) {
            std::cout << "Client disconnected" << std::endl;
            fflush(stdout);
            break;
        } else {
            std::cout << "recv failed with error: " << WSAGetLastError() << std::endl;
            closesocket(client_socket);
            WSACleanup();
            exit(1);
        }
    }


}

int TCP_server::send(const char *message) {

}



