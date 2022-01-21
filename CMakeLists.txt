cmake_minimum_required(VERSION 3.21)
project(HailMaker_httpserver)

set(CMAKE_CXX_STANDARD 17)

add_executable(HailMaker_httpserver main.cpp util/utils.cpp util/utils.h util/addr_ipv4.cpp util/addr_ipv4.h util/log.h)

target_include_directories(HailMaker_httpserver PUBLIC util)
