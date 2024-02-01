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

    for (int t = 0; t < scheduler.T; t++)
    {
        vector<pair<int, long double>> densityPerUser(scheduler.N);

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