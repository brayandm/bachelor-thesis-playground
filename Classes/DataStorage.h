#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <vector>
#include "InputStorage.h"
#include "OutputStorage.h"

class DataStorage
{
public:
    InputStorage input;
    OutputStorage output;

    std::vector<std::vector<std::vector<std::vector<double>>>> expD;
    std::vector<std::vector<int>> framesInTTI;
    std::vector<std::vector<bool>> dataUserInTTI;

    std::vector<std::vector<std::vector<double>>> dFactorPerR;
    std::vector<std::vector<double>> dFactorPerK;

    std::vector<std::vector<std::vector<double>>> dPrecal;
    std::vector<std::vector<std::vector<double>>> sPrecal;
    std::vector<std::vector<std::vector<std::vector<double>>>> s;
    std::vector<std::vector<std::vector<double>>> st;

    std::vector<double> G;

    void fitSize();
    void clear();
};

#endif // DATASTORAGE_H
