#ifndef DELIVERYCALCULATOR_H
#define DELIVERYCALCULATOR_H

#include "DataStorage.h"
#include "Precalculator.h"
#include "DataTransmissionCalculator.h"

class DeliveryCalculator
{
public:
    DeliveryCalculator(DataStorage &dataStorage);
    int calculateDelivery(DataStorage &dataStorage);
};

#endif // DELIVERYCALCULATOR_H
