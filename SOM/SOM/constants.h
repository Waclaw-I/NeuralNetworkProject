#pragma once

#include <vector>
#include "Node.h"


using dataSet = std::vector<std::vector<double>>;
using Nodes = std::vector<Node>;

const int mapWidth = 600;
const int mapHeight = 600;

const int cellsAcross = 60;
const int cellsDown = 60;

const int sizeOfInputVector = 3;

const int epochAmount = 1;
const int iterations = 1000;

const double startLearningRate = 0.1;