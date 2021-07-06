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
        srcs/Client/concrete_client_handler
)
set(My_SRCS
        srcs/config/Parser/Implementation/ConfigParser.cpp
        srcs/utils/implementation/fd_creator.cpp
        srcs/Client/concrete_client_handler/Implementation/Handler.cpp
        srcs/builders/ResponseBuilder.cpp
        srcs/manual_types.h
        srcs/builders/autoindex/AutoindexResonseBuilder.cpp
        srcs/builders/response_utils/HeadersBuilder.cpp
        srcs/builders/methods/Post.cpp
        srcs/builders/response_utils/ResponseUtils.cpp
        srcs/builders/error/ErrorBuilder.cpp
        srcs/config/Parser/Implementation/Section_impl.cpp
        srcs/utils/implementation/ParserUtils.cpp
        srcs/utils/implementation/RoutingUtils.cpp
        srcs/utils/implementation/CommonUtils.cpp
        srcs/config/repository/Implementation/ConfigRepository.cpp
        srcs/config/repository/Implementation/RouteEntity.cpp
        srcs/builders/methods/Get.cpp srcs/builders/methods/Get.hpp srcs/builders/methods/Head.cpp srcs/builders/methods/Head.hpp srcs/builders/methods/Delete.cpp srcs/builders/methods/Delete.hpp srcs/builders/cgi/CgiExecutor.cpp srcs/builders/cgi/CgiExecutor.hpp srcs/builders/methods/Put.cpp srcs/builders/methods/Put.hpp)

add_executable(web_server
        main.cpp
        ${My_SRCS})