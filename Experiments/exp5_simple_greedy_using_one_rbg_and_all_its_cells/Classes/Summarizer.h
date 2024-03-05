#ifndef SUMMARIZER_H
#define SUMMARIZER_H

#include <iostream>
#include "OutputStorage.h"
#include "Precalculator.h"
#include "DeliveryCalculator.h"

class Summarizer
{
public:
    static void summarize(DataStorage &dataStorage);
};

#endif // SUMMARIZER_H
