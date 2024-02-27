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
};

#endif // INPUTSTORAGE_H
