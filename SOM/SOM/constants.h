#pragma once

#include <vector>
#include "Node.h"


using dataSet = std::vector<std::vector<double>>;
using Nodes = std::vector<Node>;

const int mapWidth = 200;
const int mapHeight = 200;

const int cellsAcross = 20;
const int cellsDown = 20;

const int sizeOfInputVector = 3;

const int epochAmount = 4;
const int iterations = 250;

const double startLearningRate = 0.1;