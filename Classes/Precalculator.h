#ifndef PRECALCULATOR_H
#define PRECALCULATOR_H

#include <vector>
#include "DataStorage.h"
#include "InputStorage.h"
#include "Utils.h"

class Precalculator
{
public:
    void precalculateUtils(DataStorage &dataStorage);

    void precalculateFactors(DataStorage &dataStorage);
};

#endif // PRECALCULATOR_H
