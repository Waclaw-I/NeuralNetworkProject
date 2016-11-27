#include "Network.h"
#include "Input.h"
#include <iostream>

std::vector<Layer> & Network::getHiddenLayers() { return this->hiddenLayers; }
Layer & Network::getInputLayer() { return this->inputLayer; }
Layer & Network::getOutputLayer() { return this->outputLayer; }

Network::Network(int inputs, int hiddenLayers, int neuronInEachHiddenLayer, int outputs)
{
	dataSetManager.importData("digits.txt");

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

void Network::setInputValues(int record, bool isLearning)
{
	vector<vector<double>> & data = dataSetManager.inputDataSet;
	if (!isLearning) data = dataSetManager.validationInputDataSet;

	double inputsAmount = dataSetManager.inputsAmount;
	for (int i = 0; i < inputsAmount; ++i)
	{
		this->inputLayer.getNeurons()[i].getEntries()[0].setEntryValue(data[record][i]);
		this->inputLayer.getNeurons()[i].setOutput(data[record][i]); // just to be sure data is set properly
	}
}

void Network::setTargetValues(int record, bool isLearning)
{
	vector<vector<double>> & data = dataSetManager.outputDataSet;
	if (!isLearning) data = dataSetManager.validationOutputDataSet;

	double outputsAmount = dataSetManager.outputsAmount;
	for (int i = 0; i < outputsAmount; ++i)
	{
		this->outputLayer.getNeurons()[i].setTargetValue(data[record][i]);
	}
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


void Network::updateAdalineSignalErrors()
{
	for (auto & output : this->outputLayer.getNeurons())
	{
		output.calculateAdalineSignalError();
	}
	int lastHiddenLayer = this->hiddenLayers.size() - 1;

	for (int layer = lastHiddenLayer; layer >= 0; --layer)
	{
		std::vector<McCullohPitts> & actualHiddenLayerNeurons = this->hiddenLayers[layer].getNeurons();
		for (int neuron = 0; neuron < actualHiddenLayerNeurons.size(); ++neuron)
		{
			double adalineSignalError = 0;
			if (layer == lastHiddenLayer)
			{
				std::vector<McCullohPitts> & outputLayerNeurons = this->outputLayer.getNeurons();
				for (int i = 0; i < outputLayerNeurons.size(); ++i)
				{
					adalineSignalError += outputLayerNeurons[i].getEntries()[neuron].getWeight()
						* outputLayerNeurons[i].getAdalineSignalError();
				}
			}
			else
			{
				std::vector<McCullohPitts> & nextHiddenLayerNeurons = this->hiddenLayers[layer + 1].getNeurons();
				for (int i = 0; i < nextHiddenLayerNeurons.size(); ++i)
				{
					adalineSignalError += nextHiddenLayerNeurons[i].getEntries()[neuron].getWeight()
						* nextHiddenLayerNeurons[i].getAdalineSignalError();
				}
			}
			actualHiddenLayerNeurons[neuron].setAdalineSignalError(adalineSignalError);
			//cout << actualHiddenLayerNeurons[neuron].getAdalineSignalError() << endl;
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
				neurons[j].getEntries()[k].setWeight(newWeight);
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
			neurons[i].getEntries()[j].setWeight(newWeight);
		}
	}
}

void Network::updateWeightsHebbsRuleNoTeacher()
{
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
					+ 0.1
					* neurons[j].getOutputValue()
					* inputs[k].getEntryValue();
				neurons[j].getEntries()[k].setWeight(newWeight);
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
				+ 0.1
				* neurons[i].getOutputValue()
				* inputs[j].getEntryValue();
			neurons[i].getEntries()[j].setWeight(newWeight);
		}
	}
}

void Network::updateWeightsHebbsRuleWithTeacher()
{
	updateAdalineSignalErrors();

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
					+ 0.1
					* neurons[i].getAdalineSignalError()
					* inputs[k].getEntryValue();
				neurons[j].getEntries()[k].setWeight(newWeight);
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
				+ 0.1
				* neurons[i].getAdalineSignalError()
				* inputs[j].getEntryValue();
			neurons[i].getEntries()[j].setWeight(newWeight);
		}
	}
}