#include "Scheduler.h"

Scheduler::Scheduler()
{
}

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
