cmake_minimum_required(VERSION 3.15)

set(This webserver)
project(${This} CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


#add_subdirectory(googletest)

add_executable(${This} main.cpp utils.cpp core/Server.cpp core/Server.h core/Socket.cpp core/Socket.h core/Request.cpp core/Request.h core/Response.cpp core/Response.h)

#add_subdirectory(test)