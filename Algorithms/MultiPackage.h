#ifndef MULTIPACKAGE_H
#define MULTIPACKAGE_H

class MultiPackage
{
public:
    static constexpr double EPS = 1e-9;
    static const int numberOfIterations = 1;
    static constexpr double powerPerTbsLimit = 1.0;
    void run();
    void step(DataStorage &dataStorage, std::vector<int> frameIds);
};

#endif // MULTIPACKAGE_H
