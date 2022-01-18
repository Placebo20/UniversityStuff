cmake_minimum_required(VERSION 3.15)
project(Lab1_Algo)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab1_Algo DataFile.txt
        "File A.txt"
        "File B.txt"
        "File C.txt"
        "File D.txt"
        main.cpp)