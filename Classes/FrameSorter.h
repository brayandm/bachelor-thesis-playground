#ifndef FRAMESORTER_H
#define FRAMESORTER_H

#include "DataStorage.h"
#include <vector>
#include <algorithm>
#include <tuple>

class FrameSorter
{
public:
    static std::vector<int> getFramesSortByTBS(DataStorage &dataStorage);
    static std::vector<int> getFramesSortByTTI(DataStorage &dataStorage);
    static std::vector<int> getFramesSortByTTIAndTBS(DataStorage &dataStorage);
    static std::vector<int> getFramesSortByRBGConsumed(DataStorage &dataStorage);
    static std::vector<int> getFramesSortRandom(DataStorage &dataStorage);
};

#endif // FRAMESORTER_H
