#include "DataSetManager.h"
#include "RandomGenerator.h"


void DataSetManager::createTrainingSet()
{
	/*std::vector<double> 
		red,
		green,
		blue,
		yellow,
		orange,
		purple,
		dk_green,
		dk_blue;

	red.push_back(1);
	red.push_back(0);
	red.push_back(0);

	green.push_back(0);
	green.push_back(1);
	green.push_back(0);

	dk_green.push_back(0);
	dk_green.push_back(0.5);
	dk_green.push_back(0.25);

	blue.push_back(0);
	blue.push_back(0);
	blue.push_back(1);

	dk_blue.push_back(0);
	dk_blue.push_back(0);
	dk_blue.push_back(0.5);

	yellow.push_back(1);
	yellow.push_back(1);
	yellow.push_back(0.2);

	orange.push_back(1);
	orange.push_back(0.4);
	orange.push_back(0.25);

	purple.push_back(1);
	purple.push_back(0);
	purple.push_back(1);

	trainingSet.push_back(red);
	trainingSet.push_back(green);
	trainingSet.push_back(blue);
	trainingSet.push_back(yellow);
	trainingSet.push_back(orange);
	trainingSet.push_back(purple);
	trainingSet.push_back(dk_green);
	trainingSet.push_back(dk_blue);*/

	for (int i = 0; i < iterations; ++i)
	{
		std::vector<double> trainingSet;

		trainingSet.push_back(RandomGenerator::getRandomNumber());
		trainingSet.push_back(RandomGenerator::getRandomNumber());
		trainingSet.push_back(RandomGenerator::getRandomNumber());

		this->trainingSet.push_back(trainingSet);
	}
}

dataSet & DataSetManager::getDataSet() { return this->trainingSet; }