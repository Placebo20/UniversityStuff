cmake_minimum_required(VERSION 3.15)
project(I_Lab)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES Trees/Trees.cpp Trees/Trees.h main.cpp)

add_executable(I_Lab ${SOURCE_FILES})
