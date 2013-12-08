#include "BBNeuralNetwork.h"
#include "BBRandomGenerator.h"
#include "BBPerception.h"
#include "perceptions\BBPerceptionReachResource.h"
#include "perceptions\BBPerceptionSeeResource.h"
#include "perceptions\BBPerceptionResourceLocation.h"
#include "perceptions\BBPerceptionFeatureNumber.h"

#include <string.h>


namespace bitbang
{

	BBNeuralNetwork::BBNeuralNetwork(void)
	{
	}

	BBNeuralNetwork::BBNeuralNetwork(int n_hidden_layers, int hidden_neurons, int n_output_neurons,
		BBActionList& action_list, BBPerceptionList& perception_list){
			//TODO put this dynamic to detect perceptions who need more than one neuron
			n_input_neurons = perception_list.size() + 2; 
			//initial_energy = initial_energy; //TODO to remove and read from Config
			//Array Initialization
			memset(input_neurons, 0, sizeof(double)*n_input_neurons);
			memset(output_neurons, 0, sizeof(double)*n_output_neurons); 

			//Random Initialize weights
			InitializeWeights();

	}
	//TODO do a method to initialize a son with mutation value on input

	void BBNeuralNetwork::InitializeWeights(){
		//Random Initialize Weights
		weight_input_neurons  = new( double*[n_input_neurons] ); 
		for (int i = 0; i <  n_input_neurons; i++)
		{
			weight_input_neurons[i] = new (double[n_hidden_neurons]);
			for (int j = 0; j < n_hidden_neurons; j++)
			{//TODO check this
				weight_input_neurons[i][j] = (float) rand();
			}
		}	

		weight_output_neurons  = new( double*[n_hidden_neurons] ); 
		for (int i = 0; i <  n_hidden_neurons; i++)
		{
			weight_output_neurons[i] = new (double[n_output_neurons]);
			for (int j = 0; j < n_output_neurons; j++)
			{
				weight_output_neurons[i][j] = (float) rand();
			}
		}	

	}

	inline double BBNeuralNetwork::SigmoidFunction(double d_value){
		return 1.0/(1.0 + exp(-d_value));
	}

	void BBNeuralNetwork::FeedForward(){
	}

	void Clone(BBActionList& target_action_list, BBPerceptionList& target_perception_list){
	}

	void BBNeuralNetwork::FeedForward(BBPerceptionList& perception_list){
		//set input neurons to input values
		int i = 0, j, k;
		string pType;
		BBPerceptionList::iterator iPerception;

		int initial_energy = 10; //TODO Change this to read from config

		for(iPerception = perception_list.begin();
			iPerception != perception_list.end(); iPerception++ ){
				pType = (*iPerception)->GetName(); 

				if(!pType.compare("Reaching Resource")){
					BBPerceptionReachResource* pRR;
					pRR = dynamic_cast<BBPerceptionReachResource*>(*iPerception);
					//input_neurons[i] = pRR->m_bValue; //TODO FIX
					i++;
				}	

				else if(!pType.compare("Resource Location")){
					int n_res_loc;
					BBPerceptionResourceLocation* pRL;
					pRL = dynamic_cast<BBPerceptionResourceLocation*>(*iPerception);
					n_res_loc = pRL->GetValue();

					if(n_res_loc == 0){//no resource near agent
						input_neurons[i] = 0;
						input_neurons[i+1] = 0;
					}
					else if(n_res_loc == 1){//resource left of agent
						input_neurons[i] = 1;
						input_neurons[i+1] = 0;
					}
					else if(n_res_loc == 2){//resource front of agent
						input_neurons[i] = 1;
						input_neurons[i+1] = 1;
					}
					else if(n_res_loc == 3){//resource right of agent
						input_neurons[i] = 0;
						input_neurons[i+1] = 1;
					}
					i+=2;

				}

				else if(!pType.compare("Feature energy")){//check if it isnt Energy
					BBPerceptionFeatureNumber* pFN;
					pFN = dynamic_cast<BBPerceptionFeatureNumber*>(*iPerception);


					if(pFN->GetValue() >= initial_energy*0.75){//TODO change to inital Energy from Config
						input_neurons[i] = 1;
						input_neurons[i+1] = 1;
					}
					else if(pFN->GetValue() >= initial_energy*0.50){//change to inital Energy	
						input_neurons[i] = 1;
						input_neurons[i+1] = 0;
					}

					else if(pFN->GetValue() >= initial_energy*0.25){//change to inital Energy	
						input_neurons[i] = 0;
						input_neurons[i+1] = 1;
					}
					else if(pFN->GetValue() < initial_energy*0.25){//change to inital Energy	
						input_neurons[i] = 0;
						input_neurons[i+1] = 0;
					}
					i+=2;

				}
				//TODO add more hidden layers 
				//Calculate Hidden Layer values
				for(j = 0; j < n_hidden_neurons; j++){
					//clear values, necessary in this case?
					hidden_neurons[j] = 0;
					for(k=0; i <= n_input_neurons; i++ ) {
						hidden_neurons[j] += input_neurons[k] * weight_input_neurons[k][j];
					}
					//set to result of activation function
					hidden_neurons[j] = SigmoidFunction( hidden_neurons[j] );
				}

				//Calculating Output Layer values
				for(k=0; k < n_output_neurons; k++){

					output_neurons[k] = 0;		
					//get weighted sum
					for(j=0; j <= n_hidden_neurons; j++ ){
						output_neurons[k] += hidden_neurons[j] * weight_output_neurons[j][k];
					}

					//set to result of sigmoid
					output_neurons[k] = SigmoidFunction( output_neurons[k] );
					//Test purposes only////
					for(int m=0; m < n_output_neurons; m++){
						cout << "Output Neuron " << m << " value: " << output_neurons[m];
					}
					/////////////////////
					ClamOutput();

					Think();
				}
		}
	}

	BBNeuralNetwork::~BBNeuralNetwork(void)
	{
	}

	void BBNeuralNetwork::ClamOutput(){
		for(int i = 0; i < n_output_neurons; i++){
			if(output_neurons[i] < 0.5){
				output_neurons[i] = 0;
			}
			else{
				output_neurons[i] = 1;
			}
		}
	}

	list<BBAction*> BBNeuralNetwork::Think()
	{
		list<BBAction*> outputList;
		for(int k=0; k < n_output_neurons; k++){
			/*if(output_neurons[k] == 1){
			outputList.push_back(output_neurons[k]);
			}*/
		}
		/*
		for(int k=0; k < n_output_neurons; k++){
		cout << "Output Neuron " << k << " value: " << output_neurons[k];
		}
		*/
		return outputList;
	}
	string BBNeuralNetwork::HumanReadable()
	{
		for (int i = 0; i <  n_hidden_neurons; i++)
		{
			cout << "\n";
			for (int j = 0; j < n_output_neurons; j++)
			{
				cout << "Weight output neuron " << i << " " << j <<  weight_output_neurons[i][j];
			}
		}
		return "";
	}

}
