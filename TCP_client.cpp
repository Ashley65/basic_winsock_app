//
// Created by NIgel work on 14/11/2023.
//

#include <iostream>
#include "TCP_client.h"


TCP_client::TCP_client() {
    WSADATA wsaData;


    //Initialise winsock
    std::cout << "Initialising Winsock for client..." << std::endl;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "Failed. Error Code : " << WSAGetLastError() << std::endl;
        exit(1);
    }
    std::cout << "Initialised" << std::endl;

    //Create a socket
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    //Resolve the server address and port
    iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        std::cout << "getaddrinfo failed with error: " << iResult << std::endl;
        WSACleanup();
        exit(1);
    }
    std::cout << "getaddrinfo done" << std::endl;

    //Create a socket for connecting to server

    // attempt to connect to the first address returned by the call to getaddrinfo
    ptr=result;

    // Create a SOCKET for connecting to server
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
        ptr->ai_protocol);
    if (ConnectSocket == INVALID_SOCKET) {
        std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        WSACleanup();
        exit(1);
    }
    std::cout << "socket done" << std::endl;

    // Connect to server.
    connect();



}

int TCP_client::connect() {


    //Connect to remote server
    iResult = ::connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
    }

    // if connection failed then try the next address returned by getaddrinfo
    // if the socket failed to connect to any address returned by getaddrinfo

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        std::cout << "Unable to connect to server!" << std::endl;
        WSACleanup();
        exit(1);
    }
    std::cout << "Connected to server" << std::endl;



}

TCP_client::~TCP_client() {
    closesocket(socket_desc);
    WSACleanup();

}


