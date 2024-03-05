#include "DeliveryCalculator.h"

DeliveryCalculator::DeliveryCalculator(DataStorage &dataStorage)
{
    Precalculator::precalculateUtils(dataStorage);
}

int DeliveryCalculator::calculateDelivery(DataStorage &dataStorage)
{
    for (int t = 0; t < dataStorage.input.T; t++)
    {
        DataTransmissionCalculator::computeGfromPinT(dataStorage, t);
    }

    int totalDelivered = 0;

    for (int j = 0; j < dataStorage.input.J; j++)
    {
        if (dataStorage.G[j] >= dataStorage.input.TBS[j])
        {
            totalDelivered++;
        }
    }

    return totalDelivered;
}