cmake_minimum_required(VERSION 3.10)
project(homework_9)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(TBB REQUIRED tbb)
find_package(OpenCV 4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("include")

add_subdirectory(../homework_5 homework_5)

add_executable(bow src/bow.cpp)

target_link_libraries(bow convert_dataset_lib)
target_link_libraries(bow serialize_lib)
target_link_libraries(bow ${OpenCV_LIBS})
target_link_libraries(bow tbb)