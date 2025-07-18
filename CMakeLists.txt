cmake_minimum_required(VERSION 3.10)
project(udp_networking)

set(CMAKE_CXX_STANDARD 17)

# file(GLOB SRC "*.cpp")
add_executable(c_udp_server c_udp_server.cpp)
add_executable(c_udp_client c_udp_client.cpp)
