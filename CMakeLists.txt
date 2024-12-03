cmake_minimum_required(VERSION 3.10)

project(Crypt)

add_executable(main main.cpp Rsa.cpp algs.cpp Rsa.hpp algs.hpp)

set(SOURCE main.cpp Rsa.cpp algs.cpp)
set(HEADER Rsa.hpp algs.hpp)
