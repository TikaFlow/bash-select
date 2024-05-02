# This file is used to build the util library.

# get all source files
file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# create library
add_library(util STATIC)
target_sources(util PRIVATE ${SRCS})
target_include_directories(util PUBLIC ${CMAKE_SOURCE_DIR}/include)