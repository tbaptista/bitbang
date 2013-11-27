#include "BBNeuralNetwork.h"
#include "BBRandomGenerator.h"
#include <string.h>

namespace bitbang
{

BBNeuralNetwork::BBNeuralNetwork(void)
{
}
BBNeuralNetwork::BBNeuralNetwork(int n_hidden_layers, int hidden_neurons, 
		BBActionList& action_list, BBPerceptionList& perception_list){
			n_output_neurons = action_list.size;
			//TODO put this dynamic to detect perceptions who need more than one neuron
			n_input_neurons = perception_list.size + 2; 

			//Array Initialization
			memset(input_neurons, 0, sizeof(double)*n_input_neurons);
			memset(output_neurons, 0, sizeof(double)*n_output_neurons); 


			//Random Initialize weights
			InitializeWeights();

}

void BBNeuralNetwork::InitializeWeights(){
	//Random Initialize Weights
	for (int i = 0; i <  n_input_neurons; i++)
	{
		for (int j = 0; j < n_output_neurons; j++)
		{
			
		}
	}
}

inline double BBNeuralNetwork::SigmoidFunction(double d_value){
	return 1.0/(1.0 + exp(-d_value));
}

void BBNeuralNetwork::FeedForward(){
}

BBNeuralNetwork::~BBNeuralNetwork(void)
{
}
/*!
 * \brief Destructor.
 *
 */
BBNeuralNetwork::~BBNeuralNetwork(void)
{
}

list<BBAction*> BBNeuralNetwork::Think()
{

}


}