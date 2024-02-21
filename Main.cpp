#pragma GCC optimize("O3", "Ofast", "no-stack-protector", "unroll-loops", "omit-frame-pointer", "inline")

#include <bits/stdc++.h>
#include "Algorithms/Scheduler.h"

int main(int argc, char *argv[])
{
    if (argc >= 2)
        freopen(argv[1], "r", stdin);

    if (argc >= 3)
        freopen(argv[2], "w", stdout);

    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    Scheduler scheduler;

    scheduler.run();

    return 0;
}