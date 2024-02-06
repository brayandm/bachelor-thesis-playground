#!/bin/bash

read -p "Please enter the name of this experiment: " experiment_name

mkdir -p "Experiments/$experiment_name/Classes"

cp Main.cpp "Experiments/$experiment_name/Main.cpp"

cp -r Classes/* "Experiments/$experiment_name/Classes/"