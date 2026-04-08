cmake_minimum_required(VERSION 3.10)
project(network_demo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(server server.cpp)
add_executable(client client.cpp)

# target_link_libraries(server pthread)
# target_link_directories(client pthread)