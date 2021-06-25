cmake_minimum_required(VERSION 3.10)
project(homework_3)
set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.66.0 COMPONENTS filesystem)
include_directories(${Boost_INCLUDE_DIRS}) 
include_directories(${PROJECT_SOURCE_DIR})  

# Create executable to test task a
add_executable(task_a lib/HtmlWriter/html_writer.cpp)
target_link_libraries(task_a fmt)
target_link_libraries(task_a ${Boost_LIBRARIES})

# Create library from task a to include in task b
add_library(
    HtmlWriter 
    lib/HtmlWriter/html_writer.cpp 
)

# Create executable to test task b
add_executable(task_b lib/ImageBrowser/image_browser.cpp)
target_link_libraries(task_b PRIVATE HtmlWriter)