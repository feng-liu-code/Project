cmake_minimum_required(VERSION 3.10)

project(CppLearning LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 公共头文件目录,供各源文件通过 #include "direction.h" 直接引用
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# 公共库源文件目录:src/lib 下的 .cpp 是被各示例共享的实现(不含 main),
# 会被编译成静态库并链接到每个可执行目标上
file(GLOB_RECURSE LIB_CPP CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/*.cpp")

if(LIB_CPP)
    add_library(common STATIC ${LIB_CPP})
endif()

# 递归查找当前目录下所有 .cpp 文件(排除 build 目录)
file(GLOB_RECURSE ALL_CPP CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

foreach(cpp_file ${ALL_CPP})
    # 跳过任意 build 目录里的文件
    if(cpp_file MATCHES "/build/")
        continue()
    endif()

    # 跳过公共库源文件,它们不作为独立可执行目标
    if(cpp_file MATCHES "/src/lib/")
        continue()
    endif()

    # 取相对路径,例如 src/01-OverviewOfC++/HelloWorld/HelloWorld.cpp
    file(RELATIVE_PATH rel_path "${CMAKE_CURRENT_SOURCE_DIR}" "${cpp_file}")

    # CMake 内部目标名要求全局唯一,用相对路径拼成(不同目录下的同名文件也不会冲突)
    string(REGEX REPLACE "\\.cpp$" "" target_name "${rel_path}")
    string(REGEX REPLACE "[^A-Za-z0-9_]" "_" target_name "${target_name}")

    # 可执行文件的显示名用简短的源文件名,例如 HelloWorld
    get_filename_component(exe_name "${cpp_file}" NAME_WE)

    add_executable(${target_name} "${cpp_file}")

    # 链接公共库(如 direction 等共享实现)
    if(TARGET common)
        target_link_libraries(${target_name} PRIVATE common)
    endif()

    # 让可执行文件按源码目录结构输出到 build/bin 下,并使用简短文件名,方便查找和运行
    get_filename_component(rel_dir "${rel_path}" DIRECTORY)
    set_target_properties(${target_name} PROPERTIES
        OUTPUT_NAME "${exe_name}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${rel_dir}")
endforeach()
