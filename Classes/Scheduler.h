#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <iostream>
#include <iomanip>

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

    long double TBS[MAXJ];
    int userId[MAXJ];
    int firstTTI[MAXJ];
    int amountTTIs[MAXJ];
    std::vector<int> framesInTTI[MAXT];
    bool dataUserInTTI[MAXN][MAXT];

    long double p[MAXK][MAXR][MAXN][MAXT];
    bool b[MAXK][MAXR][MAXN][MAXT];

    Scheduler();

    void reader();

    void printResult();

    void summary();
};

#endif // SCHEDULER_H