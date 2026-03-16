cmake_minimum_required(VERSION 3.10)

project(BankSystem)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(BankSystem
    src/main.cpp
    src/Account.cpp
    src/BankSystem.cpp
    src/FileManager.cpp
    )