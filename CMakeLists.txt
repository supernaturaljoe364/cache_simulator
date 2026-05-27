cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

project(lru_cache)
add_executable(lru
  src/main.cpp)

target_include_directories(lru PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
