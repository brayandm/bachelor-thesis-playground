#ifndef SOLUTIONMANAGER_H
#define SOLUTIONMANAGER_H

#include "SolutionStore.h"
#include "OutputStorage.h"
#include <vector>
#include <cassert>

class SolutionManager
{
public:
    std::vector<SolutionStore> solutions;

    void addSolution(OutputStorage output, int dataFrameTransmitted);
    void clear();
    SolutionStore getBestSolution();
};

#endif // SOLUTIONMANAGER_H
