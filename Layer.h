#pragma once
#include <vector>
#include <memory>
#include "McCullohPitts.h"

class Layer
{
public:

	std::vector<McCullohPitts> & getNeurons();
	void fillInputLayer(int amount);
	void fillLayer(int amount, int eachNeuronEntries); // work as hidden / output layer

	int getSize();
private:

	std::vector<McCullohPitts>  Neurons;
};