cmake_minimum_required(VERSION 3.9)

project(cmakeresources-demo)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O0 -g")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT MSVC)
    add_compile_options(-Wall -Wextra -Werror -Wpointer-arith -Wcast-qual
        -Wno-missing-braces -Wempty-body -Wno-error=uninitialized -Wunused-function
        -Wno-error=deprecated-declarations -pedantic-errors -pedantic)
endif()

add_subdirectory(tests)
