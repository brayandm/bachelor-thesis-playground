#pragma GCC optimize("O3", "Ofast", "no-stack-protector", "unroll-loops", "omit-frame-pointer", "inline")

#include <bits/stdc++.h>
#include "Classes/Scheduler.h"

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

    vector<tuple<int, double, int>> frames;

    for (int j = 0; j < scheduler.J; j++)
    {
        frames.push_back({scheduler.amountTTIs[j], scheduler.TBS[j], j});
    }

    sort(frames.begin(), frames.end());

    vector<vector<bool>> radioOcupation(scheduler.T, vector<bool>(scheduler.R, false));

    for (auto frame : frames)
    {
        int j = get<2>(frame);

        double g = 0;

        vector<tuple<int, int, int>> ocuppiedCells;

        for (int t = scheduler.firstTTI[j]; t < scheduler.firstTTI[j] + scheduler.amountTTIs[j]; t++)
        {
            int bestRadio = -1;
            int bestCell = -1;
            double maxSINR0 = -1e9;

            for (int r = 0; r < scheduler.R; r++)
            {
                if (radioOcupation[t][r])
                    continue;

                for (int k = 0; k < scheduler.K; k++)
                {
                    if (scheduler.s0[k][r][scheduler.userId[j]][t] > maxSINR0)
                    {
                        maxSINR0 = scheduler.s0[k][r][scheduler.userId[j]][t];
                        bestRadio = r;
                        bestCell = k;
                    }
                }
            }

            if (bestRadio != -1)
            {
                radioOcupation[t][bestRadio] = true;
                ocuppiedCells.push_back({t, bestRadio, bestCell});
                scheduler.p[bestCell][bestRadio][scheduler.userId[j]][t] = 1;
                scheduler.b[bestCell][bestRadio][scheduler.userId[j]][t] = true;

                g += scheduler.computeGforFrameWithoutInterferences(j, t);

                if (g > scheduler.TBS[j] + scheduler.EPS)
                    break;
            }
        }

        if (g < scheduler.TBS[j] + scheduler.EPS)
        {
            for (auto cell : ocuppiedCells)
            {
                int t = get<0>(cell);
                int r = get<1>(cell);
                int k = get<2>(cell);

                radioOcupation[t][r] = false;
                scheduler.p[k][r][scheduler.userId[j]][t] = 0;
                scheduler.b[k][r][scheduler.userId[j]][t] = false;
            }
        }
    }

    scheduler.printResult();

    return 0;
}