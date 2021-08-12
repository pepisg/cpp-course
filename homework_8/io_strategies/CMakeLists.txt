
find_package(PNG REQUIRED)

add_library(
    libio_strategies
    io_strategy.hpp
    io_strategy.cpp
)

target_link_libraries(libio_strategies ${PNG_LIBRARY})

target_include_directories(libio_strategies PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/")