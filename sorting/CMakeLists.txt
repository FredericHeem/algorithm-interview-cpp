cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)
project (Sort)
add_executable(Sort.Test Sort.Test.cc)

include(CTest)
add_test(Sort.Test Sort.Test)
