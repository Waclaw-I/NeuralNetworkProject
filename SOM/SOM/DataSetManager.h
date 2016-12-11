#pragma once
#include "constants.h"

class DataSetManager
{
public:
	void createTrainingSet();

	dataSet & getDataSet();

private:
	dataSet trainingSet;
};