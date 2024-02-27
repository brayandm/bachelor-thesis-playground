#include "Validator.h"

void Validator::validateResult(DataStorage &dataStorage)
{
    for (int t = 0; t < dataStorage.input.T; t++)
    {
        for (int k = 0; k < dataStorage.input.K; k++)
        {
            double sumOverR = 0;

            for (int r = 0; r < dataStorage.input.R; r++)
            {
                double sumOverN = 0;

                for (int n = 0; n < dataStorage.input.N; n++)
                {
                    assert(dataStorage.output.p[k][r][n][t] >= 0);

                    assert((dataStorage.output.p[k][r][n][t] == 0) ^ dataStorage.output.b[k][r][n][t]);

                    sumOverN += dataStorage.output.p[k][r][n][t];
                }

                assert(sumOverN <= 4);

                sumOverR += sumOverN;
            }

            assert(sumOverR <= dataStorage.input.R);
        }
    }
}