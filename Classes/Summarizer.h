#ifndef SUMMARIZER_H
#define SUMMARIZER_H

#include <iostream>
#include "OutputStorage.h"
#include "Precalculator.h"
#include "DataTransmissionCalculator.h"

class Summarizer
{
public:
    void summarize(DataStorage &dataStorage, Precalculator &precalculator, DataTransmissionCalculator &dataTransmissionCalculator);
};

#endif // SUMMARIZER_H
