#!/bin/bash

ulimit -s unlimited

if [ $# -gt 0 ]; then
    echo "Error: Too many arguments" >&2
    exit 1
fi

./Build/Scheduler Tests/Example/example1
