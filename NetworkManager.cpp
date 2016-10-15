#include "NetworkManager.h"

#include <iostream>

// ie: {5,3,3,3,1} 5 inputs, 3 hidden layers with 3 neurons each, 1 output
NetworkManager::NetworkManager(vector<int> networkStructure)
{
	for (int i = 0; i < networkStructure.size(); ++i)
	{

		this->network.push_back(vector<Neuron>());
		for (int j = 0; j < networkStructure[i]; ++j)
		{
			if (i == 0)
				network.back().push_back(Neuron(1, true)); // first layer - 1 input per neuron
			else
				network.back().push_back(Neuron(networkStructure[i - 1])); // next layer - inputs = previous layer neurons amount
		}
	}
}

void NetworkManager::feedForward()
{
    for (int i = 1; i < network.size(); ++i) // for every layer except input layer
    {
        for (int j = 0; j < network[i].size(); ++j) // for every neuron in layer
        {
            for (int k = 0; k < network[i][j].getInputs().size(); k++) // for every input in neuron
            {
                network[i][j].getInputs()[k].setValue(network[i-1][k].getOutputValue());
            }
        }
    }
}

bool NetworkManager::insertData(vector<double> inputData)
{
	if (inputData.size() != network.front().size())
	{
		cout << "Input data: " << inputData.size() << " Input neurons: " << network.front().size() << endl;
		cout << "Amount of input is not equal to the amount of input neurons!" << endl;
		return false;
	}
	else
	{
		for (int i = 0; i < network.front().size(); ++i)
		{
			network.front()[i].getInputs().front().setValue(inputData[i]);
		}
		return true;
	}
}

void NetworkManager::printNetwork()
{
	char c;
	for (int i = 0; i < network.size(); ++i)
	{
		for (int j = 0; j < network[i].size(); ++j)
		{
			if (i == 0) c = 'I';
			else if (i == network.size() - 1) c = 'O';
			else c = 'N';

			cout << c << " ";
		}
		cout << "\n\n";
	}
}


vector<vector<Neuron>> & NetworkManager::getNetwork() { return this->network; }
