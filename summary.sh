#!/bin/bash

ulimit -s unlimited

if [ $# -eq 0 ]; then
    ./Build/Summary
elif [ $# -eq 1 ]; then
    ./Build/Summary "$1"
else
    ./Build/Summary "$1" "$2"
fi