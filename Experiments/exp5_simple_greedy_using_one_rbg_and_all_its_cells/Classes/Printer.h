#ifndef PRINTER_H
#define PRINTER_H

#include <iostream>
#include <iomanip>
#include "DataStorage.h"

class Printer
{
public:
    static void printResult(DataStorage &dataStorage);
    static void printResult(OutputStorage &OutputStorage);
};

#endif // PRINTER_H
