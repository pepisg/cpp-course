cmake_minimum_required(VERSION 3.10)
project(homework_5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(io_tools)

include_directories("include/")

add_executable(image src/image.cpp)
target_link_libraries(image libio_tools)