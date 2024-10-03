cmake_minimum_required(VERSION 3.26)
project(timer)

set(CMAKE_CXX_STANDARD 17)

include_directories(PRIVATE ./include)
add_library(timer src/Timer.cpp)
