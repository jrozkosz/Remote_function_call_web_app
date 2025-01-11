// Jakub Rozkosz

#ifndef EVOLUTIONARYSERVER_H
#define EVOLUTIONARYSERVER_H

#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "TCPServer.h"

class EvolutionaryServer : public TCPServer {
    private:
        bool authenticated_ = false;
        std::string userEmail_;
        int functionCallsBudget_ = 100;
        bool invalid_params_ = false;
        int pop_size_;
        int dimension_;
        int func_num_;

    public:
        EvolutionaryServer(int port);
        bool authenticate(int clientSocket);
        void getFunctionParameters(int clientSocket);
        void callObjFuncWithinBudget(int clientSocket);
        void getFuncCallsBudget(const std::string& mail);
        void handleInvalidFuncParams(int clientSocket, const std::invalid_argument& e);
};

#endif // EVOLUTIONARYSERVER_H
