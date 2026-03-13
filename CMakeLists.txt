cmake_minimum_required(VERSION 3.10.0)
project(HOTspot VERSION 0.1.0 LANGUAGES C CXX)

add_executable(HOTspot main.cpp)


# setting up the libraries for sfml nwetwork
set(SFML_DIR "<sfml-install-path>/lib/cmake/SFML") # Optional, might be needed if CMake can't find it
find_package(SFML REQUIRED COMPONENTS audio network graphics window system)
# link SFML libraries (using imported targets and PRIVATE linkage)
# the SFML targets automatically provide include directories
target_link_libraries(HOTspot PRIVATE sfml-network)

include(CTest)
enable_testing()

