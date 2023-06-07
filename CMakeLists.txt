cmake_minimum_required(VERSION 3.3)

# These configurations before "project":
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(containerbench VERSION 1.0 LANGUAGES CXX)

add_subdirectory(src)
