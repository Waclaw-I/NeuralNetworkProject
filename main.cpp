#include <iostream>
#include <memory>
#include <string>
#include <fstream>

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

int main()
{
	Network network(256, 5, 15, 10); // inputs, hidden layers, neuron in each hidden layer, outputs

	for (int epoch = 1; epoch < 10; ++epoch)
	{
		double MSE = 0;
		int records = network.dataSetManager.learningRecords;

		for (int i = 0; i < records; i++)
		{
			double uniqueMSEerror;
			network.setInputValues(i, true);
			network.setTargetValues(i, true);

			network.feedForward();
			network.updateWeights();

			uniqueMSEerror = pow(network.getOutputLayer().getNeurons()[0].getOutputValue() - network.getOutputLayer().getNeurons()[0].getTargetValue(), 2);
			MSE += uniqueMSEerror;
			network.dataSetManager.displayOneInputRecord(i);
			Layer & outputLayer = network.getOutputLayer();
			for (int outputs = 0; outputs < outputLayer.getSize(); ++outputs)
				cout << "Output " << outputs << ": " << outputLayer.getNeurons()[outputs].getOutputValue() << "\n\n";
			network.dataSetManager.displayOneOutputRecord(i);
			cout << "\n\n";
		}

		cout << "MSE: " << MSE / records << endl;
		saveMSEtoFile(to_string(MSE));
	}

	cin.get();
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