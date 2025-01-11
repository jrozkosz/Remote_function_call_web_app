// Jakub Rozkosz

#ifndef EVOLUTIONARYCLIENT_H
#define EVOLUTIONARYCLIENT_H

#include "TCPClient.h"

class EvolutionaryClient : public TCPClient {
    private:
        int dimension_, pop_size_, func_num_;
    public:
        EvolutionaryClient();
        bool authenticate(const char* email);
        void setFunctionParameters(int dimension, int population_size, int func_num);
        void objectiveFunction(double* population, double* fun_values);
        void getParams(int* params);
};

#endif // EVOLUTIONARYCLIENT_H