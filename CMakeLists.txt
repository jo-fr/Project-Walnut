cmake_minimum_required(VERSION 3.15)

set(This webserver)
project(${This} CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


#add_subdirectory(googletest)

add_executable(${This} main.cpp core/Server.cpp core/Socket.cpp http/Request.cpp http/Response.cpp http/Header.cpp)

#add_subdirectory(test)