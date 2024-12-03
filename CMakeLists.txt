cmake_minimum_required(VERSION 3.10)


project(Crypt)


add_executable(main main.cpp 
                    sources/Rsa.cpp
                    sources/algs.cpp 
                    headers/Rsa.hpp 
                    headers/algs.hpp)


set(SOURCE 
            main.cpp 
            sources/Rsa.cpp 
            sources/algs.cpp)

set(HEADER 
            headers/Rsa.hpp 
            headers/algs.hpp)
