# This file is used to build the util library.

# get all source files
file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# create library
add_library(util STATIC ${SRCS})