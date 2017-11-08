cmake_minimum_required (VERSION 2.6)
project (SparkleCode)

# require modern c++
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED on)
set (CMAKE_CXX_EXTENSIONS OFF)

# add source
include_directories("src")
add_subdirectory(src)
add_executable(SparkleCode src/main.cpp)
target_link_libraries(SparkleCode SparkleCodeMain)