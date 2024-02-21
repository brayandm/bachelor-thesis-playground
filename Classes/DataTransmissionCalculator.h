#ifndef DATATRANSMISSIONCALCULATOR_H
#define DATATRANSMISSIONCALCULATOR_H

#include "DataStorage.h"
#include <cmath>

class DataTransmissionCalculator
{
public:
    static const int W = 192;

    void computeGfromPinT(DataStorage &dataStorage, int t);

    double computeGforFrameWithoutInterferences(DataStorage &dataStorage, int j);

    double computeGforFrameWithoutInterferences(DataStorage &dataStorage, int j, int t);
};

#endif // DATATRANSMISSIONCALCULATOR_H
