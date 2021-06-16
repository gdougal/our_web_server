cmake_minimum_required(VERSION 3.17)
project(web_server)

set(CMAKE_CXX_STANDARD 14)
include_directories(srcs srcs/config)
set(My_SRCS srcs/client.cpp
         srcs/config/Config.cpp
         srcs/fd_creator.cpp
         srcs/config/HTTP_handler.cpp
         srcs/http_stuff.hpp)

add_executable(web_server
        main.cpp
        ${My_SRCS}
        )