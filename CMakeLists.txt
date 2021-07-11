cmake_minimum_required(VERSION 3.17)
project(web_server)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
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
        srcs/Client/Handler
        srcs/utils/pure_instruments
        srcs/builders/cgi
)
set(My_SRCS
        srcs/config/Parser/Implementation/ConfigParser.cpp
        srcs/config/Parser/Implementation/Section_impl.cpp
        srcs/config/repository/Implementation/ConfigRepository.cpp
        srcs/config/repository/Implementation/RouteEntity.cpp
        srcs/utils/implementation/fd_creator.cpp
        srcs/Client/Handler/Implementation/Handler.cpp
        srcs/builders/ResponseBuilder.cpp
        srcs/builders/autoindex/AutoindexResonseBuilder.cpp
        srcs/builders/response_utils/HeadersBuilder.cpp
        srcs/builders/response_utils/ResponseUtils.cpp
        srcs/builders/error/ErrorBuilder.cpp
        srcs/utils/implementation/ParserUtils.cpp
        srcs/utils/implementation/RoutingUtils.cpp
        srcs/utils/implementation/CommonUtils.cpp
        srcs/builders/cgi/CgiExecutor.cpp
        srcs/builders/methods/Post.cpp
        srcs/builders/methods/Get.cpp
        srcs/builders/methods/Head.cpp
        srcs/builders/methods/Delete.cpp
        srcs/builders/methods/Put.cpp
        )

add_executable(web_server
        main.cpp
        ${My_SRCS})