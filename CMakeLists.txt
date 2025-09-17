cmake_minimum_required(VERSION 3.24)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

project(clox LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_COMPILER clang)

add_subdirectory(src/clox)
