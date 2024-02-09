#include "Utils.h"

double Utils::geometricMean(const std::vector<double> &vect)
{
    double ans = 1;

    for (auto x : vect)
    {
        ans *= x;
    }

    return pow(ans, (double)1 / (double)vect.size());
}

double Utils::mean(const std::vector<double> &vect)
{
    double ans = 0;

    for (auto x : vect)
    {
        ans += x;
    }

    return ans / (double)vect.size();
}
