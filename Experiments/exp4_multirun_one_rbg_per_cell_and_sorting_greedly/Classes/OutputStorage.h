#ifndef OUTPUTSTORAGE_H
#define OUTPUTSTORAGE_H

#include <vector>

class OutputStorage
{
public:
    std::vector<std::vector<std::vector<std::vector<double>>>> p;
    std::vector<std::vector<std::vector<std::vector<bool>>>> b;
};

#endif // OUTPUTSTORAGE_H
