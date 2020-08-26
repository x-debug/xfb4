cmake_minimum_required(VERSION 3.5)
project(b64 C)

include_directories(inc)

set(CMAKE_C_STANDARD 99)

add_executable(b64 src/b64.c main.c)

target_link_libraries(b64 -lm)