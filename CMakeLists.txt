cmake_minimum_required(VERSION 3.10)


project(Crypt)


add_executable(main main.cpp 
                    sources/rsa/rsa.cpp
                    sources/base_crypt_algs/base_crypt_algs.cpp
                    sources/math_algs/math_algs.cpp
                    sources/rsa/rsa.hpp 
                    sources/base_crypt_algs/base_crypt_algs.hpp
                    sources/math_algs/math_algs.hpp)


set(SOURCE 
            main.cpp 
            sources/rsa/rsa.cpp
            sources/base_crypt_algs/base_crypt_algs.cpp
            sources/math_algs/math_algs.cpp)

set(HEADER 
            sources/rsa/rsa.hpp 
            sources/base_crypt_algs/base_crypt_algs.hpp
            sources/math_algs/math_algs.hpp)
