cmake_minimum_required(VERSION 3.10)

project(QuantumSimulator)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(QuantumCircuit
    src/main.cpp
    src/State.cpp
    src/Gate.cpp
    src/utils.cpp
)