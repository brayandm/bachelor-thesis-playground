#include "Precalculator.h"

void Precalculator::precalculateUtils(InputStorage &inputStorage, DataStorage &dataStorage)
{

    for (int k = 0; k < inputStorage.K; k++)
        for (int r = 0; r < inputStorage.R; r++)
            for (int m = 0; m < inputStorage.N; m++)
                for (int n = 0; n < inputStorage.N; n++)
                {
                    dataStorage.expD[k][m][r][n] = exp(-inputStorage.d[k][m][r][n]);
                }

    for (int j = 0; j < inputStorage.J; j++)
    {
        for (int t = inputStorage.firstTTI[j]; t < inputStorage.firstTTI[j] + inputStorage.amountTTIs[j]; t++)
        {
            dataStorage.framesInTTI[t].push_back(j);
            dataStorage.dataUserInTTI[inputStorage.userId[j]][t] = true;
        }
    }
}

void Precalculator::precalculateFactors(InputStorage &inputStorage, DataStorage &dataStorage)
{
    for (int k = 0; k < inputStorage.K; k++)
        for (int m = 0; m < inputStorage.N; m++)
        {
            std::vector<double> values;
            for (int r = 0; r < inputStorage.R; r++)
            {
                double up = 1;
                double down = 1;

                for (int n = 0; n < inputStorage.N; n++)
                {
                    if (m != n)
                        up *= exp(-inputStorage.d[k][m][r][n]);
                }
                for (int n = 0; n < inputStorage.N; n++)
                {
                    if (m != n)
                        for (int kt = 0; kt < inputStorage.K; kt++)
                        {
                            if (k != kt)
                                down += exp(inputStorage.d[kt][m][r][n]);
                        }
                }
                dataStorage.dFactorPerR[k][r][m] = up / down;

                values.push_back(dataStorage.dFactorPerR[k][r][m]);
            }
            dataStorage.dFactorPerK[k][m] = Utils::geometricMean(values);
        }
}