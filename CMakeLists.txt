cmake_minimum_required(VERSION 3.21)
project(HailMaker_httpserver)

set(CMAKE_CXX_STANDARD 17)

add_executable(HailMaker_httpserver main.cpp util/utils.cpp util/utils.h util/addr_ipv4.cpp util/addr_ipv4.h util/log.h util/types.h net/event_loop.cpp net/event_loop.h net/channel.cpp net/channel.h net/epoller.cpp net/epoller.h)

target_include_directories(HailMaker_httpserver PUBLIC util net)

add_executable(test test/test_event_loop.cpp util/utils.cpp util/utils.h util/addr_ipv4.cpp util/addr_ipv4.h util/log.h util/types.h net/event_loop.cpp net/event_loop.h net/channel.cpp net/channel.h net/epoller.cpp net/epoller.h)
target_include_directories(test PUBLIC util net)

#include(FetchContent)
#FetchContent_Declare(
#        googletest
#        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
#)
#FetchContent_MakeAvailable(googletest)
