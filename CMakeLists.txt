cmake_minimum_required(VERSION 3.11.0)

project(Scheduler VERSION 0.1.0)

add_executable(Scheduler Main.cpp  Classes/DataStorage.cpp Classes/DataTransmissionCalculator.cpp Classes/DeliveryCalculator.cpp Classes/FrameSorter.cpp Classes/InputReader.cpp Classes/InputStorage.cpp Classes/OutputReader.cpp Classes/OutputStorage.cpp Classes/Precalculator.cpp Classes/Printer.cpp Classes/SolutionManager.cpp Classes/SolutionStore.cpp Classes/Summarizer.cpp Classes/Utils.cpp Classes/Validator.cpp Algorithms/MultiPackage.cpp Algorithms/Scheduler.cpp Algorithms/SimpleGreedy.cpp)

add_executable(Summary Summary.cpp  Classes/DataStorage.cpp Classes/DataTransmissionCalculator.cpp Classes/DeliveryCalculator.cpp Classes/FrameSorter.cpp Classes/InputReader.cpp Classes/InputStorage.cpp Classes/OutputReader.cpp Classes/OutputStorage.cpp Classes/Precalculator.cpp Classes/Printer.cpp Classes/SolutionManager.cpp Classes/SolutionStore.cpp Classes/Summarizer.cpp Classes/Utils.cpp Classes/Validator.cpp Algorithms/MultiPackage.cpp Algorithms/Scheduler.cpp Algorithms/SimpleGreedy.cpp)

add_executable(Validate Validate.cpp  Classes/DataStorage.cpp Classes/DataTransmissionCalculator.cpp Classes/DeliveryCalculator.cpp Classes/FrameSorter.cpp Classes/InputReader.cpp Classes/InputStorage.cpp Classes/OutputReader.cpp Classes/OutputStorage.cpp Classes/Precalculator.cpp Classes/Printer.cpp Classes/SolutionManager.cpp Classes/SolutionStore.cpp Classes/Summarizer.cpp Classes/Utils.cpp Classes/Validator.cpp Algorithms/MultiPackage.cpp Algorithms/Scheduler.cpp Algorithms/SimpleGreedy.cpp)
