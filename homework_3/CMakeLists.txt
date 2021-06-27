cmake_minimum_required(VERSION 3.10)
project(homework_3)
set(CMAKE_CXX_STANDARD 17)

# Add subdirectories to libraries
add_subdirectory(lib/HtmlWriter)
add_subdirectory(lib/ImageBrowser)

add_executable(create_image_browser lib/ImageBrowser/image_browser.cpp)
target_include_directories(create_image_browser PRIVATE lib/ImageBrowser/)
target_link_libraries(create_image_browser PRIVATE HtmlWriter)