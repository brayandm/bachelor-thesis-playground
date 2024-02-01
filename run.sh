#!/bin/bash

ulimit -s unlimited

if [ $# -eq 0 ]; then
    ./Build/Scheduler
elif [ $# -eq 1 ]; then
    ./Build/Scheduler "$1"
else
    ./Build/Scheduler "$1" "$2"
fi
