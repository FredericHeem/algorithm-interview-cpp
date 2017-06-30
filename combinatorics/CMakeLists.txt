cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)
project (Sort)
add_executable(Combination Combination.cc)
add_executable(Permutation Permutation.cc)

include(CTest)
add_test(Combination Combination)
add_test(Permutation Permutation)
