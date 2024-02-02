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

long double Scheduler::geometricMean(std::vector<long double> vect)
{
    long double ans = 1;

    for (auto x : vect)
    {
        ans *= x;
    }

    return pow(ans, (long double)1 / (long double)vect.size());
}

long double Scheduler::mean(std::vector<long double> vect)
{
    long double ans = 0;

    for (auto x : vect)
    {
        ans += x;
    }

    return ans / (long double)vect.size();
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
            dFactorPerK[k][m] = geometricMean(values);
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

    std::cout << "Total delivered: " << totalDelivered << '\n';
}