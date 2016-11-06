#include <iostream>
#include <memory>

#include "RandomGenerator.h"
#include "Neuron.h"
#include "Input.h"
#include "Perceptron.h"
#include "McCullohPitts.h"
#include "Network.h"
#include "fstream"

using namespace std;

void loadTrainingData(string path, vector<vector<double>> & trainingData);
void SingleNeuronNet(Neuron * neuron);

int main()
{
	Network network(2, 2, 3, 1); // inputs, hidden layers, neuron in each hidden layer, outputs
	vector<vector<double>> trainingData;
	loadTrainingData("XORdata.txt", trainingData);

	vector<vector<double>> inputData;
	vector<double> outputData;
	for (int i = 0; i < trainingData.size(); ++i)
	{
		vector<double> temp;
		temp.push_back(trainingData[i][0]);
		temp.push_back(trainingData[i][1]);
		inputData.push_back(temp);
		outputData.emplace_back(trainingData[i][2]);
	}

	for (int epoch = 1; epoch < 100; ++epoch)
	{
		for (int i = 0; i < trainingData.size(); i++)
		{
			if (!network.setInputValues( inputData[i] )) std::cout << "Sizes of input values and input neurons are not equal!" << std::endl;
			if (!network.setTargetValues({ outputData[i] })) std::cout << "Sizes of target values and output neurons are not equal!" << std::endl;

			network.feedForward();
			network.updateWeights();

			cout << network.getInputLayer().getNeurons()[0].getOutputValue() << endl;
			cout << network.getInputLayer().getNeurons()[1].getOutputValue() << endl;
			cout << "Output: " << network.getOutputLayer().getNeurons()[0].getOutputValue() << endl;
			
		}
		
	}












	//unique_ptr<Perceptron> perceptron(new Perceptron(2));
	//unique_ptr<McCullohPitts> mcCullohPitts(new McCullohPitts(2));

	//SingleNeuronNet(perceptron.get());
	//SingleNeuronNet(mcCullohPitts.get());

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
			{
				row.push_back(temp);
			}

			if (row.size() == 3)
			{
				trainingData.push_back(row);
				row.clear();
			}
		}
	}
	else
	{
		cout << "Nie mozna otworzyc pliku!" << endl;
	}
	
}