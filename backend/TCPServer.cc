// Jakub Rozkosz

#include "TCPServer.h"
#include "../db/Database.h"
#include <string>

using namespace std;

TCPServer::TCPServer(int port) {
    serverSocket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket_ == -1) {
        cerr << "Error creating socket" << endl;
        exit(EXIT_FAILURE);
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket_, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        cerr << "Error binding socket" << endl;
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket_, 5) == -1) {
        cerr << "Error listening to socket" << endl;
        exit(EXIT_FAILURE);
    }
}

int TCPServer::acceptClient() {
    int clientSocket = accept(serverSocket_, nullptr, nullptr);
    if (clientSocket == -1) {
        cerr << "Error accepting client connection" << endl;
        exit(EXIT_FAILURE);
    }
    return clientSocket;
}

void TCPServer::sendData(int clientSocket, const void* data, size_t dataSize) {
    if (send(clientSocket, data, dataSize, 0) == -1) {
        cerr << "Error sending data" << endl;
        exit(EXIT_FAILURE);
    }
}

void TCPServer::receiveData(int clientSocket, void* buffer, size_t bufferSize) {
    if (recv(clientSocket, buffer, bufferSize, 0) == -1) {
        cerr << "Error receiving data" << endl;
        exit(EXIT_FAILURE);
    }
}

void TCPServer::closeClientConnection(int clientSocket) {
    close(clientSocket);
}

TCPServer::~TCPServer(){
    close(serverSocket_);
}
