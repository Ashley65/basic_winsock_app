#include <iostream>
#include "TCP_server.h"
#include "TCP_client.h"

int main() {
    TCP_server server;




    //Socket to listen for incoming connections
    server.listen();

    //
    TCP_client client;

    //Accept and incoming connection
    server.accept();

    //Receive a message from a client
    server.receive();

    //Send a message to the client
    server.send("Hello Client!");

    //Close the socket




}
