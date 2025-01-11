// Jakub Rozkosz

#include "EvolutionaryServer.h"
#include "../db/Database.h"
#include "cec22_test_func.h"

using namespace std;

class InvalidFunctionParamsException : public invalid_argument {
public:
    InvalidFunctionParamsException() : invalid_argument(
        "Function number should be between 1-12 and dimension in [2,10,20]") {}
};

EvolutionaryServer::EvolutionaryServer(int port) : TCPServer(port) {}

void EvolutionaryServer::callObjFuncWithinBudget(int clientSocket) {
    if (invalid_params_) {
        double population[pop_size_*dimension_];
        receiveData(clientSocket, population, sizeof(population));
        char not_auth_signal[1] = {0x04};
        sendData(clientSocket, not_auth_signal, sizeof(not_auth_signal));
        cout << "User set invalid function params." << endl;
    } else if(authenticated_) {
        SqlDatabase& db = SqlDatabase::instance();
        for (int i = 0; i < functionCallsBudget_/pop_size_; ++i) {
            double population[pop_size_*dimension_];
            receiveData(clientSocket, population, sizeof(population));

            char data_signal[1] = {0x01};
            sendData(clientSocket, data_signal, sizeof(data_signal));

            // calculating function value
            double fun_values[sizeof(pop_size_)];
            cec22_test_func(population, fun_values, dimension_, pop_size_, func_num_);

            sendData(clientSocket, fun_values, sizeof(fun_values)); 
        }

        double population[pop_size_*dimension_];
        receiveData(clientSocket, population, sizeof(population));
        char end_signal[1] = {0x02};
        sendData(clientSocket, end_signal, sizeof(end_signal));

        // update user budget
        if(functionCallsBudget_ != 0) {
            db.changeUserBudget(userEmail_, 0);
        }
    } else {
        double population[pop_size_*dimension_];
        receiveData(clientSocket, population, sizeof(population));
        char not_auth_signal[1] = {0x03};
        sendData(clientSocket, not_auth_signal, sizeof(not_auth_signal));
        cout << "User is not authenticated!" << endl;
    }
}

bool EvolutionaryServer::authenticate(int clientSocket) {
    char received_mail[256];
    receiveData(clientSocket, reinterpret_cast<char *>(&received_mail), sizeof(received_mail));
    SqlDatabase& db = SqlDatabase::instance("zpr_db.db");
    const string mail = received_mail;
    if(db.getUserId(mail) == -1) {
        const char* msg = "You're not in our database";
        sendData(clientSocket, msg, strlen(msg)+1);
        return false;
    }
    else {
        const char* msg = "Authenticated";
        sendData(clientSocket, msg, strlen(msg)+1);
        authenticated_ = true;
        userEmail_ = mail;
        getFuncCallsBudget(mail);
        return true;
    }
}

void EvolutionaryServer::getFuncCallsBudget(const string& mail) {
    SqlDatabase& db = SqlDatabase::instance("zpr_db.db");
    int budget = db.getUserBudget(mail);
    functionCallsBudget_ = budget;
}

void EvolutionaryServer::getFunctionParameters(int clientSocket) {
    int params[3];
    receiveData(clientSocket, params, sizeof(params));

    if((params[0] != 2 && params[0] != 10 && params[0] != 20) ||
        (params[2]>12 || params[2]<1)) {

        invalid_params_ = true;
    }
    dimension_ = params[0];
    pop_size_ = params[1];
    func_num_ = params[2];
}

void EvolutionaryServer::handleInvalidFuncParams(int clientSocket, const invalid_argument& e) {
    cerr << "Caught exception: " << e.what() << endl;
    closeClientConnection(clientSocket);
}