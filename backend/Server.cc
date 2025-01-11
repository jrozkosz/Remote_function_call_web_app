// Jakub Rozkosz

#include <iostream>
#include <thread>
#include <vector>
#include "EvolutionaryServer.h"

using namespace std;

void handlingClient(EvolutionaryServer& server, int clientSocket) {
    cout << "New client connected." << endl;
    server.authenticate(clientSocket);

    server.getFunctionParameters(clientSocket);

    server.callObjFuncWithinBudget(clientSocket);

    server.closeClientConnection(clientSocket);
}

int main() {
    EvolutionaryServer server(5000);
    vector<thread> threads;

    while (true) {
        int clientSocket = server.acceptClient();
        threads.emplace_back(handlingClient, ref(server), clientSocket);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
