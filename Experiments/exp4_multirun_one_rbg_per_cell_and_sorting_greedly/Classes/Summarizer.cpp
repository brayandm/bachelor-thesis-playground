#include "Summarizer.h"

void Summarizer::summarize(DataStorage &dataStorage)
{
    const std::string redColor = "\033[31m";
    const std::string yellowColor = "\033[33m";
    const std::string greenColor = "\033[32m";
    const std::string resetColor = "\033[0m";

    Precalculator::precalculateUtils(dataStorage);

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

    if ((double)totalDelivered / (double)dataStorage.input.J > 0.8)
    {
        std::cout << greenColor << "Total delivered: " << totalDelivered << " / " << dataStorage.input.J << resetColor << '\n';
    }
    else if ((double)totalDelivered / (double)dataStorage.input.J > 0.5)
    {
        std::cout << yellowColor << "Total delivered: " << totalDelivered << " / " << dataStorage.input.J << resetColor << '\n';
    }
    else
    {
        std::cout << redColor << "Total delivered: " << totalDelivered << " / " << dataStorage.input.J << resetColor << '\n';
    }
}