#ifndef INPUTSTORAGE_H
#define INPUTSTORAGE_H

#include <vector>

class InputStorage
{
public:
    int N, K, T, R, J;

    std::vector<std::vector<std::vector<std::vector<double>>>> s0;
    std::vector<std::vector<std::vector<std::vector<double>>>> d;

    std::vector<double> TBS;
    std::vector<int> userId;
    std::vector<int> firstTTI;
    std::vector<int> amountTTIs;

    InputStorage(int N, int K, int T, int R, int J,
                 const std::vector<std::vector<std::vector<std::vector<double>>>> &s0,
                 const std::vector<std::vector<std::vector<std::vector<double>>>> &d,
                 const std::vector<double> &TBS,
                 const std::vector<int> &userId,
                 const std::vector<int> &firstTTI,
                 const std::vector<int> &amountTTIs);
};

#endif // INPUTSTORAGE_H
