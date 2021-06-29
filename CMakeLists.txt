cmake_minimum_required(VERSION 3.17)
project(web_server)

set(CMAKE_CXX_STANDARD 14)
include_directories(srcs srcs/config srcs/config/repository srcs/builders srcs/builders/autoindex)
set(My_SRCS
        srcs/config/ConfigParser.cpp
        srcs/fd_creator.cpp
        srcs/config/Handler.cpp
        srcs/config/repository/ConfigRepository.hpp srcs/config/repository/RouteEntity.hpp
        srcs/builders/ResponseBuilder.cpp srcs/builders/ResponseBuilder.hpp
        srcs/http_stuff.hpp srcs/manual_types.h srcs/builders/autoindex/AutoindexResonseBuilder.cpp srcs/builders/autoindex/AutoindexResonseBuilder.hpp srcs/builders/autoindex/HeadersBuilder.cpp srcs/builders/autoindex/HeadersBuilder.hpp)

add_executable(web_server
        main.cpp
        ${My_SRCS})