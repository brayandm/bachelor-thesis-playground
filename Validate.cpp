#pragma GCC optimize("O3", "Ofast", "no-stack-protector", "unroll-loops", "omit-frame-pointer", "inline")

#include <bits/stdc++.h>
#include "Classes/InputReader.h"
#include "Classes/OutputReader.h"
#include "Classes/DataStorage.h"
#include "Classes/Validator.h"

int main(int argc, char *argv[])
{
    if (argc >= 2)
        freopen(argv[1], "r", stdin);

    if (argc >= 4)
        freopen(argv[3], "w", stdout);

    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    DataStorage dataStorage;
    InputReader::read(dataStorage.input);
    dataStorage.fitSize();

    if (argc >= 3)
        freopen(argv[2], "r", stdin);

    OutputReader::read(dataStorage.input, dataStorage.output);

    Validator::validateResult(dataStorage);

    return 0;
}