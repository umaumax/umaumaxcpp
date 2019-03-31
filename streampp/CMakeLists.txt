cmake_minimum_required(VERSION 3.5.1)

include(cmake/common/enable_libs.cmake)

enable_testing()
enable_gtest()

add_subdirectory(test)
