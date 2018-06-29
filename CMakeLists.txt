cmake_minimum_required(VERSION 2.8.9)
project (time_perf)
set (CMAKE_CXX_FLAGS "-std=c++1z -O2 --save-temps")
add_executable(time_perf time_perf.cpp)

