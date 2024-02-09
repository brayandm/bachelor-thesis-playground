#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <cmath>

class Utils
{
public:
    static double geometricMean(const std::vector<double> &vect);
    static double mean(const std::vector<double> &vect);
};

#endif // UTILS_H
