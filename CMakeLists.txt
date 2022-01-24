cmake_minimum_required(VERSION 3.5)
project(HailMaker_httpserver)

set(CMAKE_CXX_STANDARD 17)

add_executable(HailMaker_httpserver main.cpp util/utils.cpp util/utils.h util/addr_ipv4.cpp util/addr_ipv4.h util/log.h net/event_loop.cpp net/event_loop.h net/channel.cpp net/channel.h net/epoller.cpp net/epoller.h net/socket.h net/socket.cpp net/tcp_connection_manager.cpp net/tcp_connection_manager.h net/acceptor.cpp net/acceptor.h net/tcp_connection.cpp net/tcp_connection.h)

target_include_directories(HailMaker_httpserver PUBLIC util net)

add_executable(test_server test/server.cpp util/utils.cpp util/utils.h util/addr_ipv4.cpp util/addr_ipv4.h util/log.h net/event_loop.cpp net/event_loop.h net/channel.cpp net/channel.h net/epoller.cpp net/epoller.h net/socket.h net/socket.cpp net/tcp_connection_manager.cpp net/tcp_connection_manager.h net/acceptor.cpp net/acceptor.h net/tcp_connection.cpp net/tcp_connection.h)
target_include_directories(test_server PUBLIC util net)

add_executable(test_client util/utils.cpp util/utils.h util/addr_ipv4.cpp util/addr_ipv4.h util/log.h net/event_loop.cpp net/event_loop.h net/channel.cpp net/channel.h net/epoller.cpp net/epoller.h net/socket.h net/socket.cpp test/client.cpp net/tcp_connection_manager.cpp net/tcp_connection_manager.h net/acceptor.cpp net/acceptor.h net/tcp_connection.cpp net/tcp_connection.h)
target_include_directories(test_client PUBLIC util net)

#include(FetchContent)
#FetchContent_Declare(
#        googletest
#        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
#)
#FetchContent_MakeAvailable(googletest)
