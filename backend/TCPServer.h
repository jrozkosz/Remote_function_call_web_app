// Jakub Rozkosz

#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include <chrono>

class TCPServer {
private:
    int serverSocket_;

public:
    TCPServer(int port);
    ~TCPServer();
    int acceptClient();
    void closeClientConnection(int clientSocket);
    void sendData(int clientSocket, const void* data, size_t dataSize);
    void receiveData(int clientSocket, void* buffer, size_t bufferSize);
};

#endif /* TCPSERVER_H */
