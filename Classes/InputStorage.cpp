#include "InputStorage.h"

InputStorage::InputStorage(int N, int K, int T, int R, int J,
                           const std::vector<std::vector<std::vector<std::vector<double>>>> &s0,
                           const std::vector<std::vector<std::vector<std::vector<double>>>> &d,
                           const std::vector<double> &TBS,
                           const std::vector<int> &userId,
                           const std::vector<int> &firstTTI,
                           const std::vector<int> &amountTTIs)
    : N(N), K(K), T(T), R(R), J(J), s0(s0), d(d), TBS(TBS), userId(userId), firstTTI(firstTTI), amountTTIs(amountTTIs)
{
}