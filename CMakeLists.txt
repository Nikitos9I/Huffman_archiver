cmake_minimum_required(VERSION 3.9)
project(huffman_archivator)

set(CMAKE_CXX_STANDARD 14)

include_directories(library IO tester archivator)

add_executable(huffman_archivator library/tree.cpp library/tree.h library/binaryCode.h library/binaryCode.cpp library/constants.h library/innerHuffman.cpp library/innerHuffman.h IO/bufferedReader.cpp IO/bufferedReader.h archivator/archivator.cpp archivator/archivator.h tester/tester.cpp tester/tester.h main.cpp)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
    set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
endif()