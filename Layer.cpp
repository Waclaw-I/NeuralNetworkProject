#include "Layer.h"
#include "McCullohPitts.h"

std::vector<McCullohPitts> & Layer::getNeurons() { return this->Neurons; }

void Layer::fillInputLayer(int amount)
{
	for (int i = 0; i < amount; ++i)
	{
		this->Neurons.emplace_back(1, true); // entries amount, bool if this is the first layer
	}
}

void Layer::fillLayer(int amount, int eachNeuronEntries)
{
	for (int i = 0; i < amount; ++i)
	{
		this->Neurons.emplace_back(eachNeuronEntries);
	}
}

int Layer::getSize() { return this->Neurons.size(); }