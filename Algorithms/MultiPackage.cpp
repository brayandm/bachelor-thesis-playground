#include "MultiPackage.h"

void MultiPackage::run()
{
    DataStorage dataStorage;
    InputReader::read(dataStorage.input);
    dataStorage.fitSize();

    SolutionManager solutionManager;

    DeliveryCalculator deliveryCalculator(dataStorage);

    SimpleGreedy::step(dataStorage, FrameSorter::getFramesSortByTTIAndTBS(dataStorage));
    solutionManager.addSolution(dataStorage.output, deliveryCalculator.calculateDelivery(dataStorage));

    SolutionStore bestSolution = solutionManager.getBestSolution();

    Printer::printResult(bestSolution.output);
}

void MultiPackage::step(DataStorage &dataStorage, std::vector<int> frameIds)
{
}