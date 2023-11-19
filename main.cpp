#include <iostream>
#include "TCP_server.h"
#include <thread>
#include <future>
#include "TCP_client.h"

int main() {

    TCP_server server;
    std::promise<void> serverReadyPromise;
    std::future<void> serverReadyFuture = serverReadyPromise.get_future();

    //start the server in a new thread
    std::thread server_thread([&server, &serverReadyPromise](){
        server.listen();
        serverReadyPromise.set_value();
        server.accept();
         //signal that the server is ready
        while (server.receive() == 0) {
           std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        server.send("Hello from server");
        server.close();


    });

    //start the client
    TCP_client client;


    serverReadyFuture.wait(); //wait for the server to be ready
    client.send("Hello from client");

    client.receive();
    client.close();










    //send a message to the server



    server_thread.join();
}
