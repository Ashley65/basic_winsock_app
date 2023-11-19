//
// Created by NIgel work on 14/11/2023.
//

#include <iostream>
#include "TCP_client.h"
#include <thread>


TCP_client::TCP_client() {
    system("Color 0A");
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

    while(true){
        // Attempt to connect to the first address returned by
        iResult = ::connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            ptr = ptr->ai_next;
            std::cout << "Attempting to connect to server..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        else{
            //
            std::cout << "Connected to server" << std::endl;
            break;
        }

    }

    return iResult;



}

TCP_client::~TCP_client() {
    closesocket(socket_desc);
    WSACleanup();

}

int TCP_client::send(const char *message) {
    if (ConnectSocket == INVALID_SOCKET) {
        std::cout << "Unable to connect to server!" << std::endl;
        WSACleanup();
        exit(1);
    }

    std::cout << "Sending message to server..." << std::endl;
    //send an initial buffer
    iResult = ::send(ConnectSocket, message, (int) strlen(message), 0);
    if (iResult == SOCKET_ERROR) {
        std::cout << "Send failed with error: " << WSAGetLastError() << std::endl;
        closesocket(ConnectSocket);
        WSACleanup();
        exit(1);
    }
    std::cout << "Bytes Sent: " << iResult << std::endl;

    return iResult;


}

int TCP_client::receive() {
    //Receive a reply from the server
    std::cout << "Receiving message from server..." << std::endl;

    struct timeval timeout;
    timeout.tv_sec = 10; // 10 seconds
    timeout.tv_usec = 0; // Not initiating this can cause strange errors

    if (setsockopt(ConnectSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0) {
        std::cout << "setsockopt failed" <<WSAGetLastError() << std::endl;
        return 0;
    }
    std::cout << "test check 1" << std::endl;

    // receive a message from server
    while (true){
        std::cout << "test check 2" << std::endl;

        int readSize = recv(ConnectSocket, server_reply, sizeof(server_reply) , 0);
        if (readSize > 0) {
            std::cout << "Message received" << std::endl;
            std::cout << server_reply << std::endl;
            return 1;
        } else if (readSize == 0) {
            std::cout << "Client disconnected" << std::endl;
            fflush(stdout);
            break;
        } else {
            std::cout << "recv failed with error: " << WSAGetLastError() << std::endl;
            closesocket(ConnectSocket);
            WSACleanup();
            exit(1);
        }


    }
}


