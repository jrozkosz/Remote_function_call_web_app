// Jakub Rozkosz

#include <iostream>
#include "EvolutionaryClient.h"

using namespace std;

void evolutionary_alg(EvolutionaryClient client, int pop_size) {
	double population[] = {1,2,3,4,5,6,7,8};
	double received_values[pop_size];
	
	while(true) {
		try {
			client.objectiveFunction(population, received_values);
		} catch (const runtime_error& e) {
			cerr << "Caught exception: " << e.what() << endl;
			if(received_values){
				cout << "Examplary CEC fun value: " << received_values[0] << endl;
			}
			break;
		}
	}
}

int main() {
    EvolutionaryClient client;

	client.authenticate("user@gmail.com");

	int dimension = 2, pop_size = 4, func_num = 12;
	client.setFunctionParameters(dimension, pop_size, func_num);
	evolutionary_alg(client, pop_size);

    return 0;
}


