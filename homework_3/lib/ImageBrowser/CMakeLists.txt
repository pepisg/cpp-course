include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(
    ImageBrowser
    image_browser.hpp
    image_browser.cpp
)
target_link_libraries(ImageBrowser HtmlWriter)
target_include_directories(ImageBrowser PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/")
