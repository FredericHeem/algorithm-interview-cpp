cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)
project (Algo)
add_executable(BinarySearch.Test BinarySearch.Test.cc)

include(CTest)
add_test(BinarySearch.Test BinarySearch.Test)
