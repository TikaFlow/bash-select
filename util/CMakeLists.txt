# This file is used to build the util library.
set(LIB_UTIL util)
# get all source files
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRCS)
# create library
add_library(${LIB_UTIL} STATIC)
target_sources(${LIB_UTIL} PRIVATE ${SRCS})
target_include_directories(${LIB_UTIL} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)