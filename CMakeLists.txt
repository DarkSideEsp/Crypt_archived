cmake_minimum_required(VERSION 3.10)


project(Crypt)


add_executable(server server_main.cpp 
                    sources/server/server.cpp
                    sources/rsa/rsa.cpp
                    sources/base_crypt_algs/base_crypt_algs.cpp
                    sources/math_algs/math_algs.cpp

                    sources/server/server.hpp
                    sources/rsa/rsa.hpp 
                    sources/base_crypt_algs/base_crypt_algs.hpp
                    sources/math_algs/math_algs.hpp)



add_executable(listener client_listener_main.cpp 
                    sources/listener/listener.cpp
                    sources/rsa/rsa.cpp
                    sources/base_crypt_algs/base_crypt_algs.cpp
                    sources/math_algs/math_algs.cpp
                    
                    sources/listener/listener.hpp
                    sources/rsa/rsa.hpp 
                    sources/base_crypt_algs/base_crypt_algs.hpp
                    sources/math_algs/math_algs.hpp)



add_executable(writer client_writer_main.cpp 
                    sources/writer/writer.cpp
                    sources/rsa/rsa.cpp
                    sources/base_crypt_algs/base_crypt_algs.cpp
                    sources/math_algs/math_algs.cpp

                    sources/writer/writer.hpp
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
