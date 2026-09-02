cmake_minimum_required(VERSION 3.10)

project(CppLearning LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 递归查找当前目录下所有 .cpp 文件(排除 build 目录)
file(GLOB_RECURSE ALL_CPP CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

foreach(cpp_file ${ALL_CPP})
    # 跳过任意 build 目录里的文件
    if(cpp_file MATCHES "/build/")
        continue()
    endif()

    # 取相对路径,例如 01-OverviewOfC++/HelloWorld/HelloWorld.cpp
    file(RELATIVE_PATH rel_path "${CMAKE_CURRENT_SOURCE_DIR}" "${cpp_file}")

    # 把相对路径转成合法且唯一的目标名:
    # 01-OverviewOfC++/HelloWorld/HelloWorld.cpp -> 01-OverviewOfC__.HelloWorld.HelloWorld
    string(REGEX REPLACE "\\.cpp$" "" target_name "${rel_path}")
    string(REGEX REPLACE "[^A-Za-z0-9_]" "_" target_name "${target_name}")

    add_executable(${target_name} "${cpp_file}")

    # 让可执行文件按源码目录结构输出到 build/bin 下,方便查找
    get_filename_component(rel_dir "${rel_path}" DIRECTORY)
    set_target_properties(${target_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${rel_dir}")
endforeach()
