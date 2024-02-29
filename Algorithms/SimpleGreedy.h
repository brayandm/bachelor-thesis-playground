#ifndef SIMPLEGREEDY_H
#define SIMPLEGREEDY_H

#include "../Classes/InputReader.h"
#include "../Classes/DataStorage.h"
#include "../Classes/Precalculator.h"
#include "../Classes/DataTransmissionCalculator.h"
#include "../Classes/Printer.h"
#include "../Classes/FrameSorter.h"
#include "../Classes/SolutionManager.h"
#include "../Classes/SolutionStore.h"
#include "../Classes/DeliveryCalculator.h"
#include <vector>
#include <algorithm>

class SimpleGreedy
{
public:
    static const int EPS = 1e-9;
    static const int numberOfIterations = 10;
    static constexpr double initialPower = 1.0;
    void run();
    void step(DataStorage &dataStorage, std::vector<int> frameIds);
};

#endif // SIMPLEGREEDY_H
