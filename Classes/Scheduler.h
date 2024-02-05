#ifndef SCHEDULER_H
#define SCHEDULER_H

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

    std::vector<std::vector<std::vector<std::vector<long double>>>> s0;

    std::vector<std::vector<std::vector<std::vector<long double>>>> d;
    std::vector<std::vector<std::vector<std::vector<long double>>>> expD;

    std::vector<long double> TBS;
    std::vector<int> userId;
    std::vector<int> firstTTI;
    std::vector<int> amountTTIs;
    std::vector<std::vector<int>> framesInTTI;
    std::vector<std::vector<bool>> dataUserInTTI;

    std::vector<std::vector<std::vector<std::vector<long double>>>> p;
    std::vector<std::vector<std::vector<std::vector<bool>>>> b;

    std::vector<std::vector<std::vector<long double>>> dFactorPerR;
    std::vector<std::vector<long double>> dFactorPerK;

    std::vector<std::vector<std::vector<long double>>> dPrecal;
    std::vector<std::vector<std::vector<long double>>> sPrecal;
    std::vector<std::vector<std::vector<std::vector<long double>>>> s;
    std::vector<std::vector<std::vector<long double>>> st;

    std::vector<long double> G;

    Scheduler() : s0(MAXK, std::vector<std::vector<std::vector<long double>>>(MAXR, std::vector<std::vector<long double>>(MAXN, std::vector<long double>(MAXT)))),
                  d(MAXK, std::vector<std::vector<std::vector<long double>>>(MAXN, std::vector<std::vector<long double>>(MAXR, std::vector<long double>(MAXN)))),
                  expD(MAXK, std::vector<std::vector<std::vector<long double>>>(MAXN, std::vector<std::vector<long double>>(MAXR, std::vector<long double>(MAXN)))),
                  TBS(MAXJ),
                  userId(MAXJ),
                  firstTTI(MAXJ),
                  amountTTIs(MAXJ),
                  framesInTTI(MAXT, std::vector<int>()),
                  dataUserInTTI(MAXN, std::vector<bool>(MAXT)),
                  p(MAXK, std::vector<std::vector<std::vector<long double>>>(MAXR, std::vector<std::vector<long double>>(MAXN, std::vector<long double>(MAXT)))),
                  b(MAXK, std::vector<std::vector<std::vector<bool>>>(MAXR, std::vector<std::vector<bool>>(MAXN, std::vector<bool>(MAXT)))),
                  dFactorPerR(MAXK, std::vector<std::vector<long double>>(MAXR, std::vector<long double>(MAXN))),
                  dFactorPerK(MAXK, std::vector<long double>(MAXN)),
                  dPrecal(MAXK, std::vector<std::vector<long double>>(MAXR, std::vector<long double>(MAXN))),
                  sPrecal(MAXK, std::vector<std::vector<long double>>(MAXR, std::vector<long double>(MAXN))),
                  s(MAXK, std::vector<std::vector<std::vector<long double>>>(MAXR, std::vector<std::vector<long double>>(MAXN, std::vector<long double>(MAXT)))),
                  st(MAXK, std::vector<std::vector<long double>>(MAXN, std::vector<long double>(MAXT))),
                  G(MAXJ) {}

    void reader();

    void loadOutput();

    void printResult();

    long double geometricMean(std::vector<long double> vect);

    long double mean(std::vector<long double> vect);

    void precal();

    void computeGfromPinT(int t);

    void summary();
};

#endif // SCHEDULER_H