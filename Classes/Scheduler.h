#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Utils.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>

class Scheduler
{
public:
    static constexpr int W = 192;

    int N, K, T, R, J;

    std::vector<std::vector<std::vector<std::vector<double>>>> s0;

    std::vector<std::vector<std::vector<std::vector<double>>>> d;
    std::vector<std::vector<std::vector<std::vector<double>>>> expD;

    std::vector<double> TBS;
    std::vector<int> userId;
    std::vector<int> firstTTI;
    std::vector<int> amountTTIs;
    std::vector<std::vector<int>> framesInTTI;
    std::vector<std::vector<bool>> dataUserInTTI;

    std::vector<std::vector<std::vector<std::vector<double>>>> p;
    std::vector<std::vector<std::vector<std::vector<bool>>>> b;

    std::vector<std::vector<std::vector<double>>> dFactorPerR;
    std::vector<std::vector<double>> dFactorPerK;

    std::vector<std::vector<std::vector<double>>> dPrecal;
    std::vector<std::vector<std::vector<double>>> sPrecal;
    std::vector<std::vector<std::vector<std::vector<double>>>> s;
    std::vector<std::vector<std::vector<double>>> st;

    std::vector<double> G;

    Scheduler();

    void reader();

    void loadOutput();

    void printResult();

    void precal();

    void computeGfromPinT(int t);

    double computeGforFrameWithoutInterferences(int j);

    void summary();
};

#endif // SCHEDULER_H