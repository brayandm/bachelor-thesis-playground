#!/bin/bash

read -p "Please select the number of the experiment you want to load: " experiment_number

experiment_dir=$(find "Experiments/" -type d -name "exp${experiment_number}_*" -print | head -n 1)

experiment_name=$(basename "$experiment_dir")

if [[ ! -z "$experiment_name" ]]; then
    rm -rf Classes/*

    rm -f Main.cpp

    cp -r "Experiments/$experiment_name/Classes/." Classes/

    cp "Experiments/$experiment_name/Main.cpp" Main.cpp

    echo "Experiment with name $experiment_name has been loaded."
else
    echo "Error: No experiment with number $experiment_number exists." >&2
    exit 1
fi