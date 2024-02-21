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
