cmake_minimum_required(VERSION 3.12)
project(project)

enable_language(C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_definitions(BOARD=${BOARD})

add_subdirectory(bsp/${BOARD})
add_subdirectory(utils)
add_subdirectory(drivers)
add_subdirectory(hal)
add_subdirectory(external)
add_subdirectory(${CMAKE_PROJECT_NAME})
