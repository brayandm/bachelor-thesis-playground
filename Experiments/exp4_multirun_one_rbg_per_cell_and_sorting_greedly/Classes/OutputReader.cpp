#include "OutputReader.h"

void OutputReader::read(InputStorage &inputStorage, OutputStorage &outputStorage)
{
    for (int t = 0; t < inputStorage.T; t++)
    {
        for (int k = 0; k < inputStorage.K; k++)
        {
            for (int r = 0; r < inputStorage.R; r++)
            {
                for (int n = 0; n < inputStorage.N; n++)
                {
                    std::cin >> outputStorage.p[k][r][n][t];

                    if (outputStorage.p[k][r][n][t] > 0)
                    {
                        outputStorage.b[k][r][n][t] = true;
                    }
                }
            }
        }
    }
}