#pragma once
#include <list>
#include <iostream>

#include "BBBrain.h"
#include "BBAction.h"
#include "BBPerception.h"
#include "perceptions\BBPerceptionBoolean.h"
#include "perceptions\BBPerceptionNumber.h"

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
	int initial_energy;
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
		int n_output_neurons,
		BBActionList& action_list, BBPerceptionList& perception_list);
	BBNeuralNetwork(int n_hidden_layers, 
		BBActionList& action_list, BBPerceptionList& perception_list);
	BBNeuralNetwork::BBNeuralNetwork(int n_hidden_layers, int hidden_neurons, 
		BBActionList& action_list, BBPerceptionList& perception_list);

	virtual list<BBAction*> Think();
	void InitializeWeights();
	inline double SigmoidFunction(double d_value);
	void FeedForward();
	void FeedForward(BBPerceptionList& perception_list);
	void MutateWeights(float f_probability);
	void SetInputNeurons(int neurons){ n_input_neurons = neurons; }
	void SetPerceptionList(int p_list);
	void SetActionList(int a_list);
	void SetOutputNeurons(int neurons){ n_output_neurons = neurons; }
	void SetHiddenNeurons(int neurons){ n_hidden_neurons = neurons; }
	void ClamOutput();
	~BBNeuralNetwork(void);
	string HumanReadable();
};

}