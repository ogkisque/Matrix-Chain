cmake_minimum_required(VERSION 3.11)
project(MatrixChain)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=leak,address,undefined")

add_subdirectory(src)
add_subdirectory(Matrix)