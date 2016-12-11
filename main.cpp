#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <algorithm>
#include <chrono>

#include "RandomGenerator.h"
#include "Neuron.h"
#include "Input.h"
#include "Perceptron.h"
#include "McCullohPitts.h"
#include "Network.h"
#include "DataSetManager.h"


using namespace std;

void loadTrainingData(string path, vector<vector<double>> & trainingData);
void saveMSEtoFile(string MSE);
void SingleNeuronNet(Neuron * neuron);
double epochAmount = 200;

chrono::duration<double> totalTime;
chrono::duration<double> epochTime;

void ValidateNetwork(Network & network);
void StandardLearning(Network & network);
void HebbLearning(Network & network);
void WTALearning(Network & network);

int main()
{
	chrono::time_point<chrono::system_clock> start, end;

	Network network(256, 3, 15, 10); // inputs, hidden layers, neuron in each hidden layer, outputs
	int outputsAmount = network.dataSetManager.outputsAmount;
	double records = network.dataSetManager.learningRecords;
	auto & outputNeurons = network.getOutputLayer().getNeurons();

	for (int epoch = 1; epoch <= epochAmount; ++epoch)
	{
		start = chrono::system_clock::now();
		cout <<"Overall proggress: " <<  static_cast<double>(epoch / epochAmount) * 100 << "%\n\n";
		cout << "Current epoch: " << epoch << endl;
		double MSE = 0;
		//double MAPE = 0;
		

		for (int i = 0; i < records; i++)
		{
			network.setInputValues(i, true);
			network.setTargetValues(i, true);

			//StandardLearning(network);
			//HebbLearning(network);
			WTALearning(network);

			double uniqueMSEerror;
			//double uniqueMAPEerror;
			for (int j = 0; j < outputsAmount; ++j)
			{
				double difference = outputNeurons[j].getTargetValue() - outputNeurons[j].getOutputValue();
				uniqueMSEerror = pow(difference, 2);
				MSE += uniqueMSEerror;
			}
		}
		MSE /= (records);
		end = chrono::system_clock::now();
		epochTime = end - start;
		totalTime += epochTime;
		system("cls");
		
		cout << "Epoch " << epoch << " MSE: " << MSE << endl;
		//cout << "Epoch " << epoch << " MAPE: " << MAPE << "%" << endl;
		cout << "Epoch " << epoch << " Time: " << epochTime.count() << endl;
		saveMSEtoFile(to_string(MSE));
	}

	ValidateNetwork(network);


	
}

void SingleNeuronNet(Neuron * neuron)
{
	vector<vector<double>> trainingData;
	loadTrainingData("ANDdata.txt", trainingData);

	for (int epoch = 1; epoch < 20; ++epoch)
	{
		double MSE = 0;
		// how to avoid dividing by 0 in MAPE error prediction?
		//double MAPE = 0;
		cout << "\n######## Epoch number: " << epoch << " ########\n" << endl;
		for (int i = 0; i < trainingData.size(); i++)
		{
			double uniqueMSEerror = 0;
			//double uniqueMAPEerror = 0;
			for (int j = 0; j < neuron->getEntriesAmount(); j++)
			{
				neuron->getEntries()[j].setEntryValue(trainingData[i][j]);
			}
			neuron->setTargetValue(trainingData[i][2]);
			neuron->calculateOutput();
			neuron->updateWeights();

			//uniqueMAPEerror = abs((neuron->getOutputValue() - neuron->getTargetValue()) / neuron->getOutputValue());
			uniqueMSEerror = pow(neuron->getOutputValue() - neuron->getTargetValue(), 2);
			MSE += uniqueMSEerror;
			//MAPE += uniqueMAPEerror;
		}
		//cout << "MAPE: " << MAPE / trainingData.size() << endl;
		cout << "MSE: " << MSE / trainingData.size() << endl;
		cout << "Input: " << neuron->getEntries()[0].getEntryValue() << " " << neuron->getEntries()[1].getEntryValue() << endl;
		cout << "Output: " << neuron->getOutputValue() << endl;
		cout << "Target: " << neuron->getTargetValue() << endl;
		cout << "Wages: " << neuron->getEntries()[0].getWeight() << "  " << neuron->getEntries()[1].getWeight() << endl;
	}

	cin.get();
	cout << "TRAINING COMPLETED\n\n\n";

	vector<bool> inputs;
	bool temp;
	cout << "Input 1: ";
	cin >> temp;
	inputs.push_back(temp);
	cout << "Input 2: ";
	cin >> temp;
	inputs.push_back(temp);

	int i = 0;
	for (auto &entry: neuron->getEntries())
	{
		entry.setEntryValue(inputs[i]);
		++i;
	}

	neuron->calculateOutput();
	double result = neuron->getOutputValue();
	if (result > 0.99) result = 1;
	cout << "Result:	" << result;
	cin.get();
	
}
void loadTrainingData(string path, vector<vector<double>> & trainingData)
{
	fstream data;
	data.open(path, ios::in);

	if (data.good())
	{
		vector<double> row;
		double temp;

		while (!data.eof())
		{
			data >> temp;
			if (temp != 32)
				row.push_back(temp);

			if (row.size() == 3)
			{
				trainingData.push_back(row);
				row.clear();
			}
		}
	}
	else
		cout << "Nie mozna otworzyc pliku!" << endl;
}

void saveMSEtoFile(string MSE)
{
	fstream MSEFile;
	MSEFile.open("MSE.txt", ios::out | ios_base::app);
	MSEFile << MSE << endl;
}


void ValidateNetwork(Network & network)
{
	int validationRecords = network.dataSetManager.validationRecords;
	auto & outputNeurons = network.getOutputLayer().getNeurons();
	system("cls");
	cout << "\n\nOverall learning time: " << totalTime.count() << "\n\n";
	cout << "############## VALIDATION RECORDS ##############" << "\n\n";

	double overallCorrectAnswers = 0;
	double overallFalseAnswers = 0;

	vector<double> uniqueDigitCorrectAnswers(10);
	vector<double> uniqueDigitFalseAnswers(10);

	auto networkAnswer = [](auto & outputNeurons)
	{
		double answer = 0;
		for (int i = 0; i < 10; ++i)
			outputNeurons[answer].getOutputValue() > outputNeurons[i].getOutputValue() ? answer = answer : answer = i;
		return answer;
	};

	auto targetAnswer = [](auto & targetOutputs)
	{
		double answer = 0;
		for (int i = 0; i < 10; ++i)
			if (targetOutputs[i] == 1) answer = i;
		return answer;
	};

	for (int i = 0; i < validationRecords; i++)
	{
		auto & targetOutputs = network.dataSetManager.validationOutputDataSet[i];

		network.setInputValues(i, false);
		network.setTargetValues(i, false); // validation, not learning

		network.feedForward();

		int answerDigit = networkAnswer(outputNeurons);
		int targetDigit = targetAnswer(targetOutputs);
		if (answerDigit == targetDigit)
		{
			uniqueDigitCorrectAnswers[answerDigit]++;
			overallCorrectAnswers++;
		}
		else
		{
			uniqueDigitFalseAnswers[targetDigit]++;
			overallFalseAnswers++;
		}
	}

	cout << "Correct: " << overallCorrectAnswers << endl;
	cout << "False: " << overallFalseAnswers << endl;
	cout << "Network effectiveness: " << static_cast<double>(overallCorrectAnswers / (overallCorrectAnswers + overallFalseAnswers)) * 100 << "%\n\n";

	cout << "DIGIT : CORRECT | FALSE\n\n";
	for (int i = 0; i < 10; ++i)
	{
		cout << i << " : \t" << uniqueDigitCorrectAnswers[i] << "  \t" << uniqueDigitFalseAnswers[i] << endl;
	}

	cin.get();
}
void StandardLearning(Network & network)
{
	network.feedForward();
	network.updateWeights();
}

void HebbLearning(Network & network)
{
	network.feedForward();
	network.updateWeightsHebbsRuleWithTeacher();
}

void WTALearning(Network & network)
{
	network.feedForward();
	network.updateWeightsWTA();
}