cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

project(cache_simulator)
add_executable(cache_sim
  src/main.cpp)

target_include_directories(cache_sim PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
