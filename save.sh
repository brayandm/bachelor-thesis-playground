#!/bin/bash

read -p "Please enter the name of this experiment: " experiment_name

experiment_name=$(echo $experiment_name | tr '[:upper:]' '[:lower:]' | tr ' ' '_')

experiment_number=$(find Experiments -maxdepth 1 -type d | wc -l)

formatted_experiment_name="exp${experiment_number}_${experiment_name}"

mkdir -p "Experiments/$formatted_experiment_name/Classes"

cp Main.cpp "Experiments/$formatted_experiment_name/Main.cpp"

cp -r Classes/* "Experiments/$formatted_experiment_name/Classes/"