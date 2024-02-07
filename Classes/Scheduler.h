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
    static constexpr int MAXK = 10;
    static constexpr int MAXR = 10;
    static constexpr int MAXN = 100;
    static constexpr int MAXT = 1000;
    static constexpr int MAXJ = 5000;
    static constexpr int MAXS = 10000;
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

    Scheduler() : s0(MAXK, std::vector<std::vector<std::vector<double>>>(MAXR, std::vector<std::vector<double>>(MAXN, std::vector<double>(MAXT)))),
                  d(MAXK, std::vector<std::vector<std::vector<double>>>(MAXN, std::vector<std::vector<double>>(MAXR, std::vector<double>(MAXN)))),
                  expD(MAXK, std::vector<std::vector<std::vector<double>>>(MAXN, std::vector<std::vector<double>>(MAXR, std::vector<double>(MAXN)))),
                  TBS(MAXJ),
                  userId(MAXJ),
                  firstTTI(MAXJ),
                  amountTTIs(MAXJ),
                  framesInTTI(MAXT, std::vector<int>()),
                  dataUserInTTI(MAXN, std::vector<bool>(MAXT)),
                  p(MAXK, std::vector<std::vector<std::vector<double>>>(MAXR, std::vector<std::vector<double>>(MAXN, std::vector<double>(MAXT)))),
                  b(MAXK, std::vector<std::vector<std::vector<bool>>>(MAXR, std::vector<std::vector<bool>>(MAXN, std::vector<bool>(MAXT)))),
                  dFactorPerR(MAXK, std::vector<std::vector<double>>(MAXR, std::vector<double>(MAXN))),
                  dFactorPerK(MAXK, std::vector<double>(MAXN)),
                  dPrecal(MAXK, std::vector<std::vector<double>>(MAXR, std::vector<double>(MAXN))),
                  sPrecal(MAXK, std::vector<std::vector<double>>(MAXR, std::vector<double>(MAXN))),
                  s(MAXK, std::vector<std::vector<std::vector<double>>>(MAXR, std::vector<std::vector<double>>(MAXN, std::vector<double>(MAXT)))),
                  st(MAXK, std::vector<std::vector<double>>(MAXN, std::vector<double>(MAXT))),
                  G(MAXJ) {}

    void reader();

    void loadOutput();

    void printResult();

    void precal();

    void computeGfromPinT(int t);

    double computeGforFrameWithoutInterferences(int j);

    void summary();
};

#endif // SCHEDULER_H