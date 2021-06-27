find_package(Boost 1.66.0 COMPONENTS filesystem)
include_directories(${Boost_INCLUDE_DIRS}) 
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(
    HtmlWriter
    html_writer.cpp
    html_writer.hpp
)

target_link_libraries(HtmlWriter fmt)
target_link_libraries(HtmlWriter ${Boost_LIBRARIES})

target_include_directories(HtmlWriter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

