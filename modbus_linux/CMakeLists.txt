cmake_minimum_required(VERSION 3.10)
project(modbus_linux)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_compile_definitions(-Wall -Wextra -02)

add_executable(modbus_sim modbus.cpp)