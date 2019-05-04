cmake_minimum_required(VERSION 3.5 )

### c++11 standards
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project( Huffman-Compression-Algorithm )

include_directories( include )

add_executable( compress apps/compression.cpp )
add_executable( decompress apps/decompression.cpp )


