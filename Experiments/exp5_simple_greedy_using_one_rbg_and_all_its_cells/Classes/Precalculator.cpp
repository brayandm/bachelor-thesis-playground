#include "Precalculator.h"

void Precalculator::precalculateUtils(DataStorage &dataStorage)
{

    for (int k = 0; k < dataStorage.input.K; k++)
        for (int r = 0; r < dataStorage.input.R; r++)
            for (int m = 0; m < dataStorage.input.N; m++)
                for (int n = 0; n < dataStorage.input.N; n++)
                {
                    dataStorage.expD[k][m][r][n] = exp(-dataStorage.input.d[k][m][r][n]);
                }

    for (int j = 0; j < dataStorage.input.J; j++)
    {
        for (int t = dataStorage.input.firstTTI[j]; t < dataStorage.input.firstTTI[j] + dataStorage.input.amountTTIs[j]; t++)
        {
            dataStorage.framesInTTI[t].push_back(j);
            dataStorage.dataUserInTTI[dataStorage.input.userId[j]][t] = true;
        }
    }
}

void Precalculator::precalculateFactors(DataStorage &dataStorage)
{
    for (int k = 0; k < dataStorage.input.K; k++)
        for (int m = 0; m < dataStorage.input.N; m++)
        {
            std::vector<double> values;
            for (int r = 0; r < dataStorage.input.R; r++)
            {
                double up = 1;
                double down = 1;

                for (int n = 0; n < dataStorage.input.N; n++)
                {
                    if (m != n)
                        up *= exp(-dataStorage.input.d[k][m][r][n]);
                }
                for (int n = 0; n < dataStorage.input.N; n++)
                {
                    if (m != n)
                        for (int kt = 0; kt < dataStorage.input.K; kt++)
                        {
                            if (k != kt)
                                down += exp(dataStorage.input.d[kt][m][r][n]);
                        }
                }
                dataStorage.dFactorPerR[k][r][m] = up / down;

                values.push_back(dataStorage.dFactorPerR[k][r][m]);
            }
            dataStorage.dFactorPerK[k][m] = Utils::geometricMean(values);
        }
}