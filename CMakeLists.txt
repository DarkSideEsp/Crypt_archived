cmake_minimum_required(VERSION 3.10)


project(Crypt)


add_executable(main main.cpp 
                    sources/rsa/rsa.cpp
                    sources/algs/algs.cpp 
                    sources/rsa/rsa.hpp 
                    sources/algs/algs.hpp)


set(SOURCE 
            main.cpp 
            sources/rsa/rsa.cpp
            sources/algs/algs.cpp)

set(HEADER 
            sources/rsa/rsa.hpp 
            sources/algs/algs.hpp)
