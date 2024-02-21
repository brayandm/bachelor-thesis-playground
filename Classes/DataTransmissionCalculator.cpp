#include "DataTransmissionCalculator.h"

void DataTransmissionCalculator::computeGfromPinT(DataStorage &dataStorage, int t)
{
    for (int k = 0; k < dataStorage.input.K; k++)
    {
        for (int r = 0; r < dataStorage.input.R; r++)
        {
            for (int n = 0; n < dataStorage.input.N; n++)
            {
                if (dataStorage.dataUserInTTI[n][t])
                {
                    dataStorage.sPrecal[k][r][n] = 0;
                    dataStorage.dPrecal[k][r][n] = 0;
                    for (int m = 0; m < dataStorage.input.N; m++)
                    {
                        if (n != m)
                        {
                            dataStorage.sPrecal[k][r][n] += dataStorage.output.p[k][r][m][t] * dataStorage.expD[k][m][r][n];
                            dataStorage.dPrecal[k][r][n] += dataStorage.input.d[k][m][r][n] * dataStorage.output.b[k][r][m][t];
                        }
                    }
                    dataStorage.sPrecal[k][r][n] *= dataStorage.input.s0[k][r][n][t];
                }
            }
        }
    }

    for (int k = 0; k < dataStorage.input.K; k++)
    {
        for (int n = 0; n < dataStorage.input.N; n++)
        {
            dataStorage.st[k][n][t] = 1;
            int bt = 0;

            for (int r = 0; r < dataStorage.input.R; r++)
            {
                double up = dataStorage.input.s0[k][r][n][t] * dataStorage.output.p[k][r][n][t] * exp(dataStorage.dPrecal[k][r][n]);

                double down = 1;

                for (int kt = 0; kt < dataStorage.input.K; kt++)
                {
                    if (kt != k)
                    {
                        down += dataStorage.sPrecal[kt][r][n];
                    }
                }

                dataStorage.s[k][r][n][t] = up / down;

                if (dataStorage.output.b[k][r][n][t])
                {
                    dataStorage.st[k][n][t] *= dataStorage.s[k][r][n][t];
                    bt++;
                }
            }

            if (bt)
            {
                dataStorage.st[k][n][t] = pow(dataStorage.st[k][n][t], (double)1 / (double)bt);
            }
            else
            {
                dataStorage.st[k][n][t] = 0;
            }
        }
    }

    for (auto j : dataStorage.framesInTTI[t])
    {
        for (int k = 0; k < dataStorage.input.K; k++)
        {
            for (int r = 0; r < dataStorage.input.R; r++)
            {
                dataStorage.G[j] += (int)dataStorage.output.b[k][r][dataStorage.input.userId[j]][t] * log2(1 + dataStorage.st[k][dataStorage.input.userId[j]][t]) * W;
            }
        }
    }
}

double DataTransmissionCalculator::computeGforFrameWithoutInterferences(DataStorage &dataStorage, int j)
{
    double g = 0;

    for (int t = dataStorage.input.firstTTI[j]; t < dataStorage.input.firstTTI[j] + dataStorage.input.amountTTIs[j]; t++)
    {
        for (int k = 0; k < dataStorage.input.K; k++)
        {
            for (int r = 0; r < dataStorage.input.R; r++)
            {
                g += (int)dataStorage.output.b[k][r][dataStorage.input.userId[j]][t] * log2(1 + dataStorage.input.s0[k][r][dataStorage.input.userId[j]][t] * dataStorage.output.p[k][r][dataStorage.input.userId[j]][t]);
            }
        }
    }

    g *= W;

    return g;
}

double DataTransmissionCalculator::computeGforFrameWithoutInterferences(DataStorage &dataStorage, int j, int t)
{
    double g = 0;

    for (int k = 0; k < dataStorage.input.K; k++)
    {
        for (int r = 0; r < dataStorage.input.R; r++)
        {
            g += (int)dataStorage.output.b[k][r][dataStorage.input.userId[j]][t] * log2(1 + dataStorage.input.s0[k][r][dataStorage.input.userId[j]][t] * dataStorage.output.p[k][r][dataStorage.input.userId[j]][t]);
        }
    }

    g *= W;

    return g;
}