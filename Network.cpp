#include "Network.h"
#include "Input.h"
#include <iostream>

std::vector<Layer> & Network::getHiddenLayers() { return this->hiddenLayers; }
Layer & Network::getInputLayer() { return this->inputLayer; }
Layer & Network::getOutputLayer() { return this->outputLayer; }

Network::Network(int inputs, int hiddenLayers, int neuronInEachHiddenLayer, int outputs)
{
	this->inputLayer.fillInputLayer(inputs);

	for (int i = 0; i < hiddenLayers; ++i)
	{
		if (i == 0) // first hidden layer
		{
			this->hiddenLayers.push_back(Layer());
			this->hiddenLayers.back().fillLayer(neuronInEachHiddenLayer, this->inputLayer.getSize());
		}
		else
		{
			Layer previouslyLastLayer = this->hiddenLayers.back(); // our pointer to the currently last layer
			this->hiddenLayers.push_back(Layer()); // inserting new layer
			this->hiddenLayers.back().fillLayer(neuronInEachHiddenLayer, previouslyLastLayer.getSize()); // amount of neurons, amount of entries for each neuron
		}
	}

	this->outputLayer.fillLayer(outputs, this->hiddenLayers.back().getSize());
}

bool Network::setInputValues(std::vector<double> inputValues)
{
	if (this->inputLayer.getSize() != inputValues.size())
		return false;

	for (int i = 0; i < this->inputLayer.getSize(); ++i)
	{
		this->inputLayer.getNeurons()[i].getEntries()[0].setEntryValue(inputValues[i]);
		this->inputLayer.getNeurons()[i].setOutput(inputValues[i]);
	}
	return true;
}

bool Network::setTargetValues(std::vector<double> targetValues)
{
	if (this->outputLayer.getSize() != targetValues.size())
		return false;

	for (int i = 0; i < this->outputLayer.getSize(); ++i)
	{
		this->outputLayer.getNeurons()[i].setTargetValue(targetValues[i]);
	}
	return true;
}

void Network::feedForward()
{
	int layersAmount = this->hiddenLayers.size();
	for (int layer = 0; layer < layersAmount; ++layer)
	{
		int neuronsAmount = this->hiddenLayers[layer].getSize();
		for (int neuron = 0; neuron < neuronsAmount; ++neuron)
		{
			std::vector<Input> & neuronInputs = this->hiddenLayers[layer].getNeurons()[neuron].getEntries();

			int inputsAmount = neuronInputs.size();
			if (layer == 0)
				for (int input = 0; input < inputsAmount; ++input)	
					{
						neuronInputs[input].setEntryValue
							(this->inputLayer.getNeurons()[input].getEntries()[0].getEntryValue());
					}
			else
				for (int input = 0; input < inputsAmount; ++input)
				{
					neuronInputs[input].setEntryValue
						(hiddenLayers[layer - 1].getNeurons()[input].getOutputValue());
				}

			
			this->hiddenLayers[layer].getNeurons()[neuron].calculateOutput();
		}
	}

	std::vector<McCullohPitts> & lastHiddenLayerNeurons = this->hiddenLayers.back().getNeurons();
	for (auto & neuron : this->outputLayer.getNeurons())
	{
		for (int input = 0; input < neuron.getEntries().size(); ++input)
		{
			neuron.getEntries()[input].setEntryValue(lastHiddenLayerNeurons[input].getOutputValue());
		}
		neuron.calculateOutput();
	}
}

void Network::updateSignalErrors()
{
	for (auto & output : this->outputLayer.getNeurons())
	{
		output.calculateSignalError();
	}
	int lastHiddenLayer = this->hiddenLayers.size() - 1;

	for (int layer = lastHiddenLayer; layer >= 0; --layer)
	{
		std::vector<McCullohPitts> & actualHiddenLayerNeurons = this->hiddenLayers[layer].getNeurons();
		for (int neuron = 0; neuron < actualHiddenLayerNeurons.size(); ++neuron)
		{
			double signalError = 0;
			if (layer == lastHiddenLayer)
			{
				std::vector<McCullohPitts> & outputLayerNeurons = this->outputLayer.getNeurons();
				for (int i = 0; i < outputLayerNeurons.size(); ++i)
				{
					signalError += outputLayerNeurons[i].getEntries()[neuron].getWeight()
						* outputLayerNeurons[i].getSignalError();
				}
			}
			else
			{
				std::vector<McCullohPitts> & nextHiddenLayerNeurons = this->hiddenLayers[layer + 1].getNeurons();
				for (int i = 0; i < nextHiddenLayerNeurons.size(); ++i)
				{
					signalError += nextHiddenLayerNeurons[i].getEntries()[neuron].getWeight()
						* nextHiddenLayerNeurons[i].getSignalError();
				}
			}
			actualHiddenLayerNeurons[neuron].setSignalError(signalError);
		}
	}
}

void Network::updateWeights()
{
	updateSignalErrors();

	for (int i = 0; i < this->hiddenLayers.size(); ++i)
	{
		int layerSize = this->hiddenLayers[i].getSize();
		for (int j = 0; j < layerSize; ++j)
		{
			std::vector<Input> & inputs = this->hiddenLayers[i].getNeurons()[j].getEntries();
			std::vector<McCullohPitts> & neurons = this->hiddenLayers[i].getNeurons();
			for (int k = 0; k < inputs.size(); ++k)
			{
				double newWeight = inputs[k].getWeight()
					+ 0.15 // learning factor TODO: need to be in a global variable or something like that
					* neurons[j].getSignalError()
					* neurons[j].derivativeFunc()
					* inputs[k].getEntryValue();
				this->hiddenLayers[i].getNeurons()[j].getEntries()[k].setWeight(newWeight);
			}
		}
	}

	for (int i = 0; i < this->outputLayer.getSize(); ++i)
	{
		std::vector<Input> & inputs = this->outputLayer.getNeurons()[i].getEntries();
		std::vector<McCullohPitts> & neurons = this->outputLayer.getNeurons();
		for (int j = 0; j < inputs.size(); ++j)
		{
			double newWeight = inputs[j].getWeight()
				+ 0.15 // learning factor TODO: need to be in a global variable or something like that
				* neurons[i].getSignalError()
				* neurons[i].derivativeFunc()
				* inputs[j].getEntryValue();
			this->outputLayer.getNeurons()[i].getEntries()[j].setWeight(newWeight);
		}
	}
}