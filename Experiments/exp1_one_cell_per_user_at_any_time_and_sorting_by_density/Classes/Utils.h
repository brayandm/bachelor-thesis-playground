#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <cmath>

class Utils
{
public:
    static long double geometricMean(const std::vector<long double> &vect);
    static long double mean(const std::vector<long double> &vect);
};

#endif // UTILS_H
