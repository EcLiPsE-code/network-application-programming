cmake_minimum_required(VERSION 3.17)
project(Lab1_version_2_)

set(CMAKE_CXX_STANDARD 14)

add_executable(server server.cpp)
add_executable(client client.cpp)

if(WIN32)
    target_link_libraries(server ws2_32)
    target_link_libraries(client ws2_32)
endif()