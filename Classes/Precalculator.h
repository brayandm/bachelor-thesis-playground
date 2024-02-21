#ifndef PRECALCULATOR_H
#define PRECALCULATOR_H

#include <vector>
#include "DataStorage.h"
#include "InputStorage.h"
#include "Utils.h"

class Precalculator
{
public:
    void precalculateUtils(InputStorage &inputStorage, DataStorage &dataStorage);

    void precalculateFactors(InputStorage &inputStorage, DataStorage &dataStorage);
};

#endif // PRECALCULATOR_H
