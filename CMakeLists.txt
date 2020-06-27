cmake_minimum_required(VERSION 3.17.0)

# set the project name
project(Project)

# ensure C++20
set(CMAKE_CXX_STANDARD 20)

# add the executable
add_executable(LinkedList src/LinkedList.cpp)