#include "Utils.h"

long double Utils::geometricMean(const std::vector<long double> &vect)
{
    long double ans = 1;

    for (auto x : vect)
    {
        ans *= x;
    }

    return pow(ans, (long double)1 / (long double)vect.size());
}

long double Utils::mean(const std::vector<long double> &vect)
{
    long double ans = 0;

    for (auto x : vect)
    {
        ans += x;
    }

    return ans / (long double)vect.size();
}
