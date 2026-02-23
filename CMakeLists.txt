cmake_minimum_required(VERSION 3.16)
project(prog3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE ALL_CPP_FILES "${CMAKE_SOURCE_DIR}/*.cpp")

foreach(CPP_FILE IN LISTS ALL_CPP_FILES)
    file(RELATIVE_PATH REL_PATH ${CMAKE_SOURCE_DIR} ${CPP_FILE})
    string(REPLACE "/" "_" TARGET_NAME ${REL_PATH})
    string(REPLACE "\\" "_" TARGET_NAME ${TARGET_NAME})
    string(REPLACE ".cpp" "" TARGET_NAME ${TARGET_NAME})
    add_executable(${TARGET_NAME} ${CPP_FILE})
endforeach()
