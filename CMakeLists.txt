cmake_minimum_required(VERSION 3.17)
project(GameOfLife C)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_executable(GameOfLife
        main.c)

target_link_libraries(GameOfLife ${SDL2_LIBRARIES})