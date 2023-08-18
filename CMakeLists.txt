cmake_minimum_required(VERSION 3.11-3.18)

set (CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

project(mdc)

add_executable(mdc main.cpp utils.cpp reader.cpp workspace.cpp compiler.cpp)
