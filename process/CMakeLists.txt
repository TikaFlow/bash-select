# This file is used to build the process library.

# get all source files
file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# create library
add_library(process STATIC ${SRCS})
target_link_libraries(process util)