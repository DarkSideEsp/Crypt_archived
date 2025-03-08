cmake_minimum_required(VERSION 3.10)


project(Server/Client)

add_executable(server server_main.cpp 
                    sources/rsa/rsa.cpp
                    sources/base_crypt_algs/base_crypt_algs.cpp
                    sources/math_algs/math_algs.cpp
                    sources/server/server.cpp

                    sources/rsa/rsa.hpp 
                    sources/base_crypt_algs/base_crypt_algs.hpp
                    sources/math_algs/math_algs.hpp
                    sources/server/server.hpp)

add_executable(client client_main.cpp 
                    sources/rsa/rsa.cpp
                    sources/base_crypt_algs/base_crypt_algs.cpp
                    sources/math_algs/math_algs.cpp
                    sources/client/client.cpp

                    sources/rsa/rsa.hpp 
                    sources/base_crypt_algs/base_crypt_algs.hpp
                    sources/math_algs/math_algs.hpp
                    sources/client/client.hpp)

add_executable(main main.cpp 
                    sources/rsa/rsa.cpp
                    sources/base_crypt_algs/base_crypt_algs.cpp
                    sources/math_algs/math_algs.cpp

                    sources/rsa/rsa.hpp 
                    sources/base_crypt_algs/base_crypt_algs.hpp
                    sources/math_algs/math_algs.hpp)

