cmake_minimum_required(VERSION 3.10)
project(c-cpp-demos LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# 遍历所有子目录，每个demo是独立的子项目
# 递归查找所有包含 CMakeLists.txt 的子目录
file(GLOB_RECURSE cmake_files RELATIVE ${CMAKE_SOURCE_DIR} demos/*/CMakeLists.txt)
foreach(cmake_file ${cmake_files})
    get_filename_component(dir ${cmake_file} DIRECTORY)
    add_subdirectory(${dir})
endforeach()
