#include "BBNeuralNetwork.h"
#include "BBRandomGenerator.h"
#include "BBPerception.h"
#include "perceptions\BBPerceptionReachResource.h"
#include "perceptions\BBPerceptionSeeResource.h"
#include "perceptions\BBPerceptionResourceLocation.h"
#include <string.h>

namespace bitbang
{

	BBNeuralNetwork::BBNeuralNetwork(void)
	{
	}

	BBNeuralNetwork::BBNeuralNetwork(int n_hidden_layers, int hidden_neurons, int n_output_neurons,
		BBActionList& action_list, BBPerceptionList& perception_list ){
			//TODO put this dynamic to detect perceptions who need more than one neuron
			n_input_neurons = perception_list.size + 2; 

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
				weight_input_neurons[i][j] = (float) rand();
			}
		}	

	}

	inline double BBNeuralNetwork::SigmoidFunction(double d_value){
		return 1.0/(1.0 + exp(-d_value));
	}

	void BBNeuralNetwork::FeedForward(){
	}

	void BBNeuralNetwork::FeedForward(BBPerceptionList& perception_list){
		//set input neurons to input values
		int i = 0, j, k;
		string pType;
		BBPerceptionList::iterator iPerception;
		for(iPerception = perception_list.begin();
			iPerception != perception_list.end(); iPerception++ ){
				pType = (*iPerception)->GetName(); 
				if(!pType.compare("Reaching Resource")){
					input_neurons[i] = (*iPerception)->GetOpCount;
					i++;
				}	

				else if(!pType.compare("Resource Location")){

					int n_res_loc = (*iPerception)->GetOpCount;
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
					if((*iPerception)->GetOpCount >= 10*0.75){//TODO change to inital Energy
						input_neurons[i] = 1;
						input_neurons[i+1] = 1;
					}
					else if((*iPerception)->GetOpCount >= 10*0.50){//change to inital Energy	
						input_neurons[i] = 1;
						input_neurons[i+1] = 0;
					}
					else if((*iPerception)->GetOpCount >= 10*0.25){//change to inital Energy	
						input_neurons[i] = 0;
						input_neurons[i+1] = 1;
					}
					else if((*iPerception)->GetOpCount < 10*0.25){//change to inital Energy	
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

					Think();
				}
		}
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
		//Clam output and choose according actions 
		for(int k=0; k < n_output_neurons; k++){
			cout << "Output Neuron " << k << " value: " << output_neurons[k];
		}
	}
}