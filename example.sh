#!/bin/bash

ulimit -s unlimited

if [ $# -gt 0 ]; then
    echo "Error: Too many arguments" >&2
    exit 1
fi

echo "Building..."

error_output=$(bash build.sh 2>&1 > /dev/null)

if [ $? -ne 0 ]; then 
    echo -e "\033[31m$error_output\033[0m"
    exit 1
fi

./Build/Scheduler Tests/Example/example1
