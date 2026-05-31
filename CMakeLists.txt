cmake_minimum_required(VERSION 3.23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

project(cache_simulator)
add_executable(cache_sim
  src/main.cpp
  src/fifo.cpp
) 

target_include_directories(cache_sim PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
#since this is a header only library, tarhet_include_directories

configure_file(test/sample.txt
                ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)





#[[add_library(mylib)

target_sources(mylib
    PRIVATE
      libraby_immplementation.cpp

    PUBLIC
      FILE_SET HEADERS
      BASE_DIR include
      FILES
        include/header1.h
)

target_link_libraries(cache_sim PRIVATE mylib)


if you got header only lib (include), and its implementation on another .cpp file, use this
]]#

