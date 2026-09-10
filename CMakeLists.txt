cmake_minimum_required(VERSION 3.31.12)

project(R5A12 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_TOOLCHAIN_FILZ conanfile.txt)

add_subdirectory("src")