// Jakub Rozkosz

#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

class TCPClient {
private:
    int clientSocket_;

public:
    TCPClient();
    ~TCPClient();
    void connectToServer(const char* ipAddress, int port);
    void sendData(const void* data, size_t dataSize);
    void receiveData(void* buffer, size_t bufferSize);
};

#endif // TCPCLIENT_H
