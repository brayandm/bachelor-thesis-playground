#ifndef SCHEDULEONERUN_H
#define SCHEDULEONERUN_H

#include "InputStorage.h"
#include "InputReader.h"
#include "DataStorage.h"
#include "OutputStorage.h"
#include "Precalculator.h"
#include "DataTransmissionCalculator.h"
#include "Printer.h"
#include <vector>
#include <algorithm>

class ScheduleOneRun
{
public:
    static const int EPS = 1e-9;
    void run();
};

#endif // SCHEDULEONERUN_H
