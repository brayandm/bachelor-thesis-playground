#include "SimpleGreedy.h"

void SimpleGreedy::run()
{
    DataStorage dataStorage;
    InputReader::read(dataStorage.input);
    dataStorage.fitSize();

    SimpleGreedy::step(dataStorage, FrameSorter::getFramesSortByTTIAndTBS(dataStorage));

    Printer::printResult(dataStorage);
}

void SimpleGreedy::step(DataStorage &dataStorage, std::vector<int> frameIds)
{
}