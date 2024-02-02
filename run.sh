#!/bin/bash

ulimit -s unlimited

if [ $# -gt 2 ]; then
    echo "Error: Too many arguments" >&2
    exit 1
fi

if [ $# -eq 0 ]; then
    ./Build/Scheduler
elif [ $# -eq 1 ]; then
    ./Build/Scheduler "$1"
else
    ./Build/Scheduler "$1" "$2"
fi
