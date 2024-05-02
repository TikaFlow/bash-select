# cmake版本限制
cmake_minimum_required(VERSION 3.15)

message(STATUS ">> CMake version: ${CMAKE_VERSION}")
message(STATUS ">> CMake generator: ${CMAKE_GENERATOR}")

# 项目语言
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 项目信息
project(bash-sql LANGUAGES CXX VERSION 0.1.0 DESCRIPTION "Using SQL-like languages to process lightweight data in bash."
        HOMEPAGE_URL "https://github.com/TikaFlow/bash-sql")

# 头文件搜索路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 子目录
add_subdirectory(util)
add_subdirectory(process)

# get all source files
file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
# add executable target
add_executable(sql ${SRCS})
target_link_libraries(sql util process)