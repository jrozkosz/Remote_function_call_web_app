// Jakub Rozkosz

#include "TCPClient.h"

using namespace std;

TCPClient::TCPClient() {
    clientSocket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket_ == -1) {
        cerr << "Error creating socket" << endl;
        exit(EXIT_FAILURE);
    }
}

void TCPClient::connectToServer(const char* ipAddress, int port) {
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = inet_addr(ipAddress);

    if (connect(clientSocket_, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        cerr << "Connection failed" << endl;
        exit(EXIT_FAILURE);
    }
}

void TCPClient::sendData(const void* data, size_t dataSize) {
    if (send(clientSocket_, data, dataSize, 0) == -1) {
        cerr << "Error sending data" << endl;
        exit(EXIT_FAILURE);
    }
}

void TCPClient::receiveData(void* buffer, size_t bufferSize) {
    if (recv(clientSocket_, buffer, bufferSize, 0) == -1) {
        cerr << "Error receiving data" << endl;
        exit(EXIT_FAILURE);
    }
}

TCPClient::~TCPClient() {
    cout << "Closing connection..." << endl;
    close(clientSocket_);
}
