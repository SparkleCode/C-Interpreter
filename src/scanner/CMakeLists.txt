# require modern c++
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED on)
set (CMAKE_CXX_EXTENSIONS OFF)

project(Scanner)

add_library(Scanner Token.cpp Scanner.cpp)