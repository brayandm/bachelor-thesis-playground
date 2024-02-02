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

    long double s0[MAXK][MAXR][MAXN][MAXT];

    long double d[MAXK][MAXN][MAXR][MAXN];
    long double expD[MAXK][MAXN][MAXR][MAXN];

    long double TBS[MAXJ];
    int userId[MAXJ];
    int firstTTI[MAXJ];
    int amountTTIs[MAXJ];
    std::vector<int> framesInTTI[MAXT];
    bool dataUserInTTI[MAXN][MAXT];

    long double p[MAXK][MAXR][MAXN][MAXT];
    bool b[MAXK][MAXR][MAXN][MAXT];

    long double dFactorPerR[MAXK][MAXR][MAXN];
    long double dFactorPerK[MAXK][MAXN];

    long double dPrecal[MAXK][MAXR][MAXN];
    long double sPrecal[MAXK][MAXR][MAXN];
    long double s[MAXK][MAXR][MAXN][MAXT];
    long double st[MAXK][MAXN][MAXT];

    long double G[MAXJ];

    Scheduler();

    void reader();

    void printResult();

    long double geometricMean(std::vector<long double> vect);

    long double mean(std::vector<long double> vect);

    void precal();

    void computeGfromPinT(int t);

    void summary();
};

#endif // SCHEDULER_H