#pragma once

#include "Neuron.h"
#include <vector>

using namespace std;

class NetworkManager
{
public:
	NetworkManager() = delete;
	NetworkManager(vector<int> networkStructure);
	bool insertData(vector<double> inputData, vector<double> outputData);
	void feedForward();
	void updateWeights();
	void printNetwork();

	vector<vector<Neuron>> & getNetwork();
private:
	vector<vector<Neuron>> network;
};