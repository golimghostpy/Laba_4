cmake_minimum_required(VERSION 3.29)
project(Laba_4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY /home/golimghost/Desktop/CProj/Laba_4/bin)
include_directories(.)

add_executable(main
        main.cpp
        structures.cpp
        structures.h
        task2.cpp
        task2.h
        task1.cpp
        task1.h
        task3.cpp
        task3.h
)
