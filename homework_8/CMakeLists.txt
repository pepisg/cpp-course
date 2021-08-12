cmake_minimum_required(VERSION 3.10)
project(homework_8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PNG REQUIRED)
add_subdirectory(io_strategies)
include_directories(include)

add_executable(task_1 src/task_1.cpp)
add_executable(image src/image.cpp include/image.hpp)
target_link_libraries(image ${PNG_LIBRARY})
target_link_libraries(image libio_strategies)