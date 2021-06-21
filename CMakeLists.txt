cmake_minimum_required(VERSION 3.4)

project(log)

set(CMAKE_CXX_STANDARD 17)

add_executable(log test.cpp logger.hpp logger.cpp)
