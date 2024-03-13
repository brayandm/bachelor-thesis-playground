#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include <vector>
#include <tuple>
#include "DataStorage.h"

class Transformer
{
public:
    std::vector < std::tuple<int, int, int, int, bool> rb;
    std::vector < std::tuple<int, int, int, int, double> rp;

    void rollBack(DataStorage &dataStorage);
    bool scheduleFrameOnShareCellKeepingDataTransmission(DataStorage &dataStorage, int frameId, int t, int r, int k);
};

#endif // TRANSFORMER_H
