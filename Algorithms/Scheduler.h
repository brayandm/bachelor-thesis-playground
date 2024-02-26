#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "../Classes/InputReader.h"
#include "../Classes/DataStorage.h"
#include "../Classes/Precalculator.h"
#include "../Classes/DataTransmissionCalculator.h"
#include "../Classes/Printer.h"
#include <vector>
#include <algorithm>

class Scheduler
{
public:
    static const int EPS = 1e-9;
    static const int numberOfIterations = 100;
    void run();
};

#endif // SCHEDULER_H
