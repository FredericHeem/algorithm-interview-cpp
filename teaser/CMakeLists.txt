cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)
project (Sort)
add_executable(Matriochka Matriochka.cc)

include(CTest)
add_test(Matriochka Matriochka)
