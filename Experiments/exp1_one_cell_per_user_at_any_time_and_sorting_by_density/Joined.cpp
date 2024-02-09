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

    void precal();

    void computeGfromPinT(int t);

    void summary();
};

#endif // SCHEDULER_H
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <cmath>

class Utils
{
public:
    static long double geometricMean(const std::vector<long double> &vect);
    static long double mean(const std::vector<long double> &vect);
};

#endif // UTILS_H




void Scheduler::reader()
{
    std::cin >> N >> K >> T >> R;

    for (int t = 0; t < T; t++)
        for (int k = 0; k < K; k++)
            for (int r = 0; r < R; r++)
                for (int n = 0; n < N; n++)
                    std::cin >> s0[k][r][n][t];

    for (int k = 0; k < K; k++)
        for (int r = 0; r < R; r++)
            for (int m = 0; m < N; m++)
                for (int n = 0; n < N; n++)
                {
                    std::cin >> d[k][m][r][n];
                    expD[k][m][r][n] = exp(-d[k][m][r][n]);
                }

    std::cin >> J;

    for (int j = 0; j < J; j++)
    {
        int id;
        std::cin >> id >> TBS[j] >> userId[j] >> firstTTI[j] >> amountTTIs[j];

        for (int t = firstTTI[j]; t < firstTTI[j] + amountTTIs[j]; t++)
        {
            framesInTTI[t].push_back(id);
            dataUserInTTI[userId[j]][t] = true;
        }
    }
}

void Scheduler::loadOutput()
{
    for (int t = 0; t < T; t++)
    {
        for (int k = 0; k < K; k++)
        {
            for (int r = 0; r < R; r++)
            {
                for (int n = 0; n < N; n++)
                {
                    std::cin >> p[k][r][n][t];

                    if (p[k][r][n][t] > 0)
                    {
                        b[k][r][n][t] = true;
                    }
                }
            }
        }
    }
}

void Scheduler::printResult()
{
    for (int t = 0; t < T; t++)
    {
        for (int k = 0; k < K; k++)
        {
            for (int r = 0; r < R; r++)
            {
                for (int n = 0; n < N; n++)
                {
                    std::cout << std::fixed << std::setprecision(5) << p[k][r][n][t] << " ";
                }
                std::cout << '\n';
            }
        }
    }
}

void Scheduler::precal()
{
    for (int k = 0; k < K; k++)
        for (int m = 0; m < N; m++)
        {
            std::vector<long double> values;
            for (int r = 0; r < R; r++)
            {
                long double up = 1;
                long double down = 1;

                for (int n = 0; n < N; n++)
                {
                    if (m != n)
                        up *= exp(-d[k][m][r][n]);
                }
                for (int n = 0; n < N; n++)
                {
                    if (m != n)
                        for (int kt = 0; kt < K; kt++)
                        {
                            if (k != kt)
                                down += exp(d[kt][m][r][n]);
                        }
                }
                dFactorPerR[k][r][m] = up / down;

                values.push_back(dFactorPerR[k][r][m]);
            }
            dFactorPerK[k][m] = Utils::geometricMean(values);
        }
}

void Scheduler::computeGfromPinT(int t)
{
    for (int k = 0; k < K; k++)
    {
        for (int r = 0; r < R; r++)
        {
            for (int n = 0; n < N; n++)
            {
                if (dataUserInTTI[n][t])
                {
                    sPrecal[k][r][n] = 0;
                    dPrecal[k][r][n] = 0;
                    for (int m = 0; m < N; m++)
                    {
                        if (n != m)
                        {
                            sPrecal[k][r][n] += p[k][r][m][t] * expD[k][m][r][n];
                            dPrecal[k][r][n] += d[k][m][r][n] * b[k][r][m][t];
                        }
                    }
                    sPrecal[k][r][n] *= s0[k][r][n][t];
                }
            }
        }
    }

    for (int k = 0; k < K; k++)
    {
        for (int n = 0; n < N; n++)
        {
            st[k][n][t] = 1;
            int bt = 0;

            for (int r = 0; r < R; r++)
            {
                long double up = s0[k][r][n][t] * p[k][r][n][t] * exp(dPrecal[k][r][n]);

                long double down = 1;

                for (int kt = 0; kt < K; kt++)
                {
                    if (kt != k)
                    {
                        down += sPrecal[kt][r][n];
                    }
                }

                s[k][r][n][t] = up / down;

                if (b[k][r][n][t])
                {
                    st[k][n][t] *= s[k][r][n][t];
                    bt++;
                }
            }

            if (bt)
            {
                st[k][n][t] = pow(st[k][n][t], (long double)1 / (long double)bt);
            }
            else
            {
                st[k][n][t] = 0;
            }
        }
    }

    for (auto j : framesInTTI[t])
    {
        for (int k = 0; k < K; k++)
        {
            for (int r = 0; r < R; r++)
            {
                G[j] += (int)b[k][r][userId[j]][t] * log2(1 + st[k][userId[j]][t]) * W;
            }
        }
    }
}

void Scheduler::summary()
{
    const std::string redColor = "\033[31m";
    const std::string yellowColor = "\033[33m";
    const std::string greenColor = "\033[32m";
    const std::string resetColor = "\033[0m";

    precal();

    for (int t = 0; t < T; t++)
    {
        computeGfromPinT(t);
    }

    int totalDelivered = 0;

    for (int j = 0; j < J; j++)
    {
        if (G[j] >= TBS[j])
        {
            totalDelivered++;
        }
    }

    if ((long double)totalDelivered / (long double)J > 0.8)
    {
        std::cout << greenColor << "Total delivered: " << totalDelivered << " / " << J << resetColor << '\n';
    }
    else if ((long double)totalDelivered / (long double)J > 0.5)
    {
        std::cout << yellowColor << "Total delivered: " << totalDelivered << " / " << J << resetColor << '\n';
    }
    else
    {
        std::cout << redColor << "Total delivered: " << totalDelivered << " / " << J << resetColor << '\n';
    }
}


long double Utils::geometricMean(const std::vector<long double> &vect)
{
    long double ans = 1;

    for (auto x : vect)
    {
        ans *= x;
    }

    return pow(ans, (long double)1 / (long double)vect.size());
}

long double Utils::mean(const std::vector<long double> &vect)
{
    long double ans = 0;

    for (auto x : vect)
    {
        ans += x;
    }

    return ans / (long double)vect.size();
}


#pragma GCC optimize("O3", "Ofast", "no-stack-protector", "unroll-loops", "omit-frame-pointer", "inline")

#include <bits/stdc++.h>


using namespace std;

#ifdef LOCAL
#define debugMode true
#include "/home/brayand/debugger.h"
#else
#define debugMode false
#define db(...) false
#define dbl(...) false
#define dbg(...) false
#define dbm(...) false
#define dbs(...) false
#define dbas(...) false
#endif

int32_t main(int argc, char *argv[])
{
    if (argc >= 2)
        freopen(argv[1], "r", stdin);

    if (argc >= 3)
        freopen(argv[2], "w", stdout);

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    Scheduler scheduler;

    scheduler.reader();

    for (int t = 0; t < scheduler.T; t++)
    {
        vector<pair<int, long double>> densityPerUser;

        for (int n = 0; n < scheduler.N; n++)
            densityPerUser.push_back({n, 0});

        for (auto j : scheduler.framesInTTI[t])
        {
            long double density = scheduler.TBS[j] / (long double)scheduler.amountTTIs[j];

            densityPerUser[scheduler.userId[j]].second += density;
        }

        sort(densityPerUser.begin(), densityPerUser.end(), [](pair<int, long double> a, pair<int, long double> b)
             { return a.second > b.second; });

        int pos = 0;

        for (int k = 0; k < scheduler.K; k++)
        {
            for (int r = 0; r < scheduler.R; r++)
            {
                if (pos < scheduler.N)
                {
                    scheduler.p[k][r][densityPerUser[pos].first][t] = 1;
                    scheduler.b[k][r][densityPerUser[pos].first][t] = true;
                    pos++;
                }
            }
        }
    }

    scheduler.printResult();

    return 0;
}