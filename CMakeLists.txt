cmake_minimum_required(VERSION 3.17)
project(web_server)

set(CMAKE_CXX_STANDARD 14)
include_directories(
        srcs
        srcs/config
        srcs/config/repository
        srcs/builders
        srcs/builders/autoindex
        srcs/builders/methods
        srcs/Client
        srcs/builders/response_utils
        srcs/builders/error
        srcs/utils
)
set(My_SRCS
        srcs/config/ConfigParser.cpp
        srcs/fd_creator.cpp
        srcs/Client/concrete_client_handler/Handler.cpp
        srcs/builders/ResponseBuilder.cpp
        srcs/manual_types.h
        srcs/builders/autoindex/AutoindexResonseBuilder.cpp
        srcs/builders/response_utils/HeadersBuilder.cpp
        srcs/builders/methods/Post.cpp
        srcs/builders/response_utils/ResponseUtils.cpp
        srcs/builders/error/ErrorBuilder.cpp)

add_executable(web_server
        main.cpp
        ${My_SRCS})