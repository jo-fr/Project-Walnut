cmake_minimum_required(VERSION 3.15)

set(This webserver)
project(${This} CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -Wall -Werror -Wextra -g")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")


#add_subdirectory(googletest)

add_executable(${This} main.cpp core/Server.cpp core/Socket.cpp http/Request.cpp http/Response.cpp http/Header.cpp utils.cpp)

#add_subdirectory(test)
