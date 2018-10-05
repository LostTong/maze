# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
# 项目信息
project (Maze)
# add include
include_directories(./args)
include_directories(./constants)
include_directories(./data)
include_directories(./generators)
# main
add_executable(Maze ./main.cpp ./args/action.cpp ./args/arg_processor.cpp ./data/maze.cpp ./generators/recursivegen.cpp ./generators/recursivegen_stack.cpp)