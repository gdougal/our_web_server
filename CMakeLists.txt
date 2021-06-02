cmake_minimum_required(VERSION 3.17)
project(web_server)

set(CMAKE_CXX_STANDARD 14)
include_directories(srcs srcs/config)
set(My_SRCS srcs/Bridge.cpp
         srcs/Server.cpp
         srcs/config/Config.cpp)

add_executable(web_server
        main.cpp
        ${My_SRCS}
        )