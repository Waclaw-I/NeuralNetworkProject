#pragma once
#include <vector>
#include "Layer.h"
#include "DataSetManager.h"


class Network
{
public:
	Network(int inputs, int hiddenLayers, int neuronInEachHiddenLayer, int outputs );
	std::vector<Layer> & getHiddenLayers();
	Layer & getInputLayer();
	Layer & getOutputLayer();

	void setInputValues(int record, bool isLearning);
	void setTargetValues(int record, bool isLearning);
	void feedForward();
	void updateWeights();
	void updateWeightsWTA();
	void updateWeightsHebbsRuleNoTeacher();
	void updateWeightsHebbsRuleWithTeacher();

	DataSetManager dataSetManager;
private:

	Layer inputLayer;
	Layer outputLayer;
	std::vector<Layer> hiddenLayers;

	void updateSignalErrors();
	void updateAdalineSignalErrors();
};