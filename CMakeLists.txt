cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
project(Compression)

add_executable(app main.cpp bit_io/bit_io.cpp huffman_code/huffman_code.cpp arithmetic_code/arith_model.cpp)