#include "Printer.h"

void Printer::printResult(DataStorage &dataStorage)
{
    for (int t = 0; t < dataStorage.input.T; t++)
    {
        for (int k = 0; k < dataStorage.input.K; k++)
        {
            for (int r = 0; r < dataStorage.input.R; r++)
            {
                for (int n = 0; n < dataStorage.input.N; n++)
                {
                    std::cout << std::fixed << std::setprecision(5) << dataStorage.output.p[k][r][n][t] << " ";
                }
                std::cout << '\n';
            }
        }
    }
}

void Printer::printResult(OutputStorage &outputStorage)
{
    int K = outputStorage.p.size();
    int R = outputStorage.p[0].size();
    int N = outputStorage.p[0][0].size();
    int T = outputStorage.p[0][0][0].size();

    for (int t = 0; t < T; t++)
    {
        for (int k = 0; k < K; k++)
        {
            for (int r = 0; r < R; r++)
            {
                for (int n = 0; n < N; n++)
                {
                    std::cout << std::fixed << std::setprecision(5) << outputStorage.p[k][r][n][t] << " ";
                }
                std::cout << '\n';
            }
        }
    }
}