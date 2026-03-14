cmake_minimum_required(VERSION 3.10.0)
project(HOTspot VERSION 0.1.0 LANGUAGES C CXX)

add_executable(HOTspot main.cpp src/PortScanner.cpp)

include(CTest)
enable_testing()

