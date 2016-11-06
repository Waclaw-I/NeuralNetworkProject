#pragma once
#include <vector>
#include "Layer.h"


class Network
{
public:
	Network(int inputs, int hiddenLayers, int neuronInEachHiddenLayer, int outputs );
	std::vector<Layer> & getHiddenLayers();
	Layer & getInputLayer();
	Layer & getOutputLayer();

	bool setInputValues(std::vector<double>);
	bool setTargetValues(std::vector<double> targetValues);
	void feedForward();
	void updateWeights();
private:

	Layer inputLayer;
	Layer outputLayer;
	std::vector<Layer> hiddenLayers;

	void updateSignalErrors();
};