# This file is used to build the process library.
set(LIB_NAME process)
# get all source files
file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# create library
add_library(${LIB_NAME} STATIC)
target_sources(${LIB_NAME} PRIVATE ${SRCS})
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${LIB_NAME} util)