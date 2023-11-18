#include <iostream>
#include "TCP_server.h"
#include <thread>
#include "TCP_client.h"

int main() {

    TCP_server server;
    bool serverReady = false;

    //start the server in a new thread
    std::thread server_thread([&server, &serverReady](){
        server.listen();
        server.accept();
        serverReady = true;
        while (server.receive() == 0) {
           std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

    });
    //start the client
    TCP_client client;

    //give the server time to start
    while (!serverReady) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }



    //send a message to the server
    client.send("Hello from client");


    server_thread.join();
}
