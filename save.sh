#!/bin/bash

read -p "Please enter the name of this experiment: " experiment_name

read -p "Please enter the description of this experiment: " experiment_description

experiment_name_snake_cased=$(echo $experiment_name | tr '[:upper:]' '[:lower:]' | tr ' ' '_')

experiment_number=$(find Experiments -maxdepth 1 -type d | wc -l)

formatted_experiment_name="exp${experiment_number}_${experiment_name_snake_cased}"

mkdir -p "Experiments/$formatted_experiment_name/Classes"

cp Main.cpp "Experiments/$formatted_experiment_name/Main.cpp"

cp -r Classes/* "Experiments/$formatted_experiment_name/Classes/"

echo "{
  \"name\": \"$experiment_name\",
  \"description\": \"$experiment_description\"
}" > "Experiments/${formatted_experiment_name}/Description.json"