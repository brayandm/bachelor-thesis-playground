cmake_minimum_required(VERSION 3.11.0)

project(Scheduler VERSION 0.1.0)

add_executable(Scheduler Main.cpp Classes/Scheduler.cpp)

add_executable(Summary Summary.cpp Classes/Scheduler.cpp)