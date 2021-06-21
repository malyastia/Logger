<<<<<<< HEAD
cmake_minimum_required(VERSION 3.4)
=======
cmake_minimum_required(VERSION 3.20)
>>>>>>> 313c421befdd7dc9e92e26aae85e5416413bcc32

project(log)

set(CMAKE_CXX_STANDARD 17)

add_executable(log test.cpp logger.hpp logger.cpp)
