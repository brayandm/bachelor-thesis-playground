#ifndef OUTPUTREADER_H
#define OUTPUTREADER_H

#include <iostream>
#include "InputStorage.h"
#include "OutputStorage.h"

class OutputReader
{
public:
    void read(InputStorage &inputStorage, OutputStorage &outputStorage);
};

#endif // OUTPUTREADER_H
