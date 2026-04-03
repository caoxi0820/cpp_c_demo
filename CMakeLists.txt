cmake_minimum_required(VERSION 3.10)
project(c-cpp-demos LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# 遍历所有子目录，每个demo是独立的子项目
file(GLOB demo_dirs RELATIVE ${CMAKE_SOURCE_DIR} demos/*)
foreach(dir ${demo_dirs})
    if(EXISTS "${CMAKE_SOURCE_DIR}/${dir}/CMakeLists.txt")
        add_subdirectory(${dir})
    endif()
endforeach()
