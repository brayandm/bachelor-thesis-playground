#!/bin/bash

ulimit -s unlimited

if [ $# -gt 3 ]; then
    echo "Error: Too many arguments" >&2
    exit 1
fi

if [ $# -lt 2 ]; then
    echo "Error: Too few arguments" >&2
    exit 1
elif [ $# -eq 2 ]; then
    ./Build/Summary "$1" "$2"
else
    ./Build/Summary "$1" "$2" "$3"
fi