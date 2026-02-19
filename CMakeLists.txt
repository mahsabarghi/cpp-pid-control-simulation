cmake_minimum_required(VERSION 3.16)
project(cpp_pid_control_simulation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cpp_pid_control_simulation
    src/main.cpp
)

target_include_directories(cpp_pid_control_simulation PRIVATE src)

