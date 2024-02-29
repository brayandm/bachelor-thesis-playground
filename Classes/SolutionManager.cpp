#include "SolutionManager.h"

void SolutionManager::addSolution(OutputStorage output, int dataFrameTransmitted)
{
    SolutionStore solution;
    solution.output = output;
    solution.dataFrameTransmitted = dataFrameTransmitted;
    solutions.push_back(solution);
}

void SolutionManager::clear()
{
    solutions.clear();
}

SolutionStore SolutionManager::getBestSolution()
{
    assert(solutions.size() > 0);

    SolutionStore bestSolution = solutions[0];

    for (int i = 1; i < solutions.size(); i++)
    {
        if (solutions[i].dataFrameTransmitted > bestSolution.dataFrameTransmitted)
        {
            bestSolution = solutions[i];
        }
    }
    return bestSolution;
}