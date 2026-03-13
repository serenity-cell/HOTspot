cmake_minimum_required(VERSION 3.10.0)
project(HOTspot VERSION 0.1.0 LANGUAGES C CXX)

add_executable(HOTspot main.cpp)


# setting up the libraries for sfml nwetwork
find_package(Boost REQUIRED)
# link SFML libraries (using imported targets and PRIVATE linkage)
# the SFML targets automatically provide include directories
target_link_libraries(HOTspot PRIVATE boost-asio)

include(CTest)
enable_testing()

