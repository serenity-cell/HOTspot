cmake_minimum_required(VERSION 3.10.0)
project(HOTspot VERSION 0.2.2 LANGUAGES C CXX)

add_executable(HOTspot main.cpp src/PortScanner.cpp)

include(CTest)
enable_testing()

