#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "DataStorage.h"
#include <cassert>

class Validator
{
public:
    static void validateResult(DataStorage &dataStorage);
};

#endif // VALIDATOR_H
