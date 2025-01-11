// Jakub Rozkosz

#include <stdexcept>
#include "EvolutionaryClient.h"

using namespace std;

class BudgetExhaustedException : public std::runtime_error {
public:
    BudgetExhaustedException() : std::runtime_error("Function calls budget exhausted!") {}
};

class NotAuthenticatedException : public std::runtime_error {
public:
    NotAuthenticatedException() : std::runtime_error("You're not authenticated!") {}
};

class UnexpectedMessageTypeException : public std::runtime_error {
public:
    UnexpectedMessageTypeException() : std::runtime_error("Unexpected message type received.") {}
};

class InvalidFunctionParamsException : public std::runtime_error {
public:
    InvalidFunctionParamsException() : std::runtime_error(
        "Function number should be between 1-12 and dimension in [2,10,20]") {}
};


EvolutionaryClient::EvolutionaryClient() {
    connectToServer("127.0.0.1", 5000);
}

bool EvolutionaryClient::authenticate(const char* email) {
    std::cout<<"Authentication initialization..."<<std::endl;
    sendData(email, strlen(email)+1);
    std::cout<<"Sent email..."<<std::endl;
    char received_msg[256];
	receiveData(reinterpret_cast<void*>(&received_msg), sizeof(received_msg));
	std::cout << "Received msg from server: " << received_msg << std::endl;
    std::cout << "\nStarted sending data... \n" << std::endl;
    return true;
}

void EvolutionaryClient::objectiveFunction(double* population, double* fun_values) {
    sendData(population, sizeof(double)*pop_size_*dimension_);
    char buffer[1];
    receiveData(buffer, sizeof(buffer));
    // std::cout << "Received message type: " << static_cast<int>(buffer[0]) << std::endl;
    if (buffer[0] == 0x01) {
        receiveData(fun_values, sizeof(double)*pop_size_);
    } else if (buffer[0] == 0x02) {
        throw BudgetExhaustedException();
    } else if (buffer[0] == 0x03) {
        throw NotAuthenticatedException();
    } else if (buffer[0] == 0x04) {
        throw InvalidFunctionParamsException();
    } else {
        throw UnexpectedMessageTypeException();
    }
}

void EvolutionaryClient::setFunctionParameters(int dimension, int population_size, int func_num) {
    const int params[] = {dimension, population_size, func_num};
    sendData(params, sizeof(params));

    this->dimension_ = dimension;
    this->pop_size_ = population_size;
    this->func_num_ = func_num;
}

void EvolutionaryClient::getParams(int* params) {
    params[0] = dimension_;
    params[1] = pop_size_;
    params[2] = func_num_;
}