cmake_minimum_required(VERSION 3.10)
project(homework_5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV 4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("include")
message(STATUS, ${OpenCV_INCLUDE_DIRS})


add_executable(serialize src/serialize.cpp)
target_link_libraries(serialize ${OpenCV_LIBS})