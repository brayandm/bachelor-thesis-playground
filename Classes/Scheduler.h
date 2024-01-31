#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <iostream>

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

    Scheduler();

    void reader()
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
                        std::cin >> d[k][m][r][n];

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
};

#endif