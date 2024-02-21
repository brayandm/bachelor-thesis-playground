#ifndef PRINTER_H
#define PRINTER_H

#include <iostream>
#include <iomanip>
#include "DataStorage.h"

class Printer
{
public:
    void printResult(DataStorage &dataStorage);
};

#endif // PRINTER_H
