#!/bin/bash

rm -f CMakeLists.txt

echo "cmake_minimum_required(VERSION 3.11.0)" >> CMakeLists.txt
echo "" >> CMakeLists.txt
echo "project(Scheduler VERSION 0.1.0)" >> CMakeLists.txt
echo "" >> CMakeLists.txt

headers=""

for file in $(ls Classes/*.cpp)
do
    headers="$headers $file"
done

for file in $(ls Algorithms/*.cpp)
do
    headers="$headers $file"
done

echo $headers

echo "add_executable(Scheduler Main.cpp $headers)" >> CMakeLists.txt
echo "" >> CMakeLists.txt
echo "add_executable(Summary Summary.cpp $headers)" >> CMakeLists.txt
echo "" >> CMakeLists.txt
echo "add_executable(Validate Validate.cpp $headers)" >> CMakeLists.txt