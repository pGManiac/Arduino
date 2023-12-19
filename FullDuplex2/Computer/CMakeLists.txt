cmake_minimum_required(VERSION 3.26)
project(Computer)

set(CMAKE_CXX_STANDARD 14)

add_executable(Computer
        FullDuplexComputer.cpp
        Frame.hpp
        Queue.hpp
        SerialPort.hpp
        SerialPort.cpp
        Frame.cpp
        Queue.cpp
        testHardwareBytes.cpp
)
