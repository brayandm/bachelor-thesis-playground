#include <InputReader.h>

void InputReader::read(InputStorage &inputStorage)
{
    std::cin >> inputStorage.N >> inputStorage.K >> inputStorage.T >> inputStorage.R;

    for (int t = 0; t < inputStorage.T; t++)
        for (int k = 0; k < inputStorage.K; k++)
            for (int r = 0; r < inputStorage.R; r++)
                for (int n = 0; n < inputStorage.N; n++)
                    std::cin >> inputStorage.s0[k][r][n][t];

    for (int k = 0; k < inputStorage.K; k++)
        for (int r = 0; r < inputStorage.R; r++)
            for (int m = 0; m < inputStorage.N; m++)
                for (int n = 0; n < inputStorage.N; n++)
                    std::cin >> inputStorage.d[k][m][r][n];

    std::cin >> inputStorage.J;

    inputStorage.TBS.resize(inputStorage.J);
    inputStorage.userId.resize(inputStorage.J);
    inputStorage.firstTTI.resize(inputStorage.J);
    inputStorage.amountTTIs.resize(inputStorage.J);

    for (int j = 0; j < inputStorage.J; j++)
    {
        int id;
        std::cin >> id >> inputStorage.TBS[j] >> inputStorage.userId[j] >> inputStorage.firstTTI[j] >> inputStorage.amountTTIs[j];
    }
}