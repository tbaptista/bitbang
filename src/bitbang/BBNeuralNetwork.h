#pragma once
#include <list>
#include <iostream>

#include "BBBrain.h"
#include "BBAction.h"
#include "BBPerception.h"


using namespace std;

namespace bitbang
{

class BBNeuralNetwork : public BBBrain
{
private:
	//neurons number
	int n_hidden_neurons;
	int n_input_neurons;
	int n_output_neurons;

	int n_hidden_layers;
	//TODO replace this for lists?
	//neurons
	double* hidden_neurons;
	double* input_neurons;
	double* output_neurons;

	//weights
	double** weight_input_neurons;
	double** weight_output_neurons;

public:
	BBNeuralNetwork();
	BBNeuralNetwork(int n_hidden_layers, int hidden_neurons, 
		int n_output_neurons, int n_input_neurons,
		BBActionList& action_list, BBPerceptionList& perception_list);
	//TODO Possibility of know nNeurons from list sizes??
	BBNeuralNetwork(int n_hidden_layers, 
		BBActionList& action_list, BBPerceptionList& perception_list);
	BBNeuralNetwork::BBNeuralNetwork(int n_hidden_layers, int hidden_neurons, 
		BBActionList& action_list, BBPerceptionList& perception_list);
	virtual list<BBAction*> Think();
	void InitializeWeights();
	inline double SigmoidFunction(double d_value);
	void FeedForward();
	void MutateWeights(float f_probability);
	~BBNeuralNetwork(void);
	string HumanReadable();
};

}