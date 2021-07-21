cmake_minimum_required(VERSION 3.10)
project(homework_5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV 4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("include")
message(STATUS, ${OpenCV_INCLUDE_DIRS})

add_library(
    serialize_lib
    src/serialize.cpp
    include/serialize.hpp
)

add_library(
    convert_dataset_lib
    src/convert_dataset.cpp
    include/convert_dataset.hpp
)

target_include_directories(convert_dataset_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_include_directories(serialize_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(convert_dataset_lib serialize_lib)



# add_executable(serialize src/serialize.cpp)
# target_link_libraries(serialize ${OpenCV_LIBS})
add_executable(convert_dataset src/convert_dataset.cpp)
target_link_libraries(convert_dataset ${OpenCV_LIBS})
target_link_libraries(convert_dataset serialize_lib)