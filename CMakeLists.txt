cmake_minimum_required(VERSION 3.5)
project(HailMaker_httpserver)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(HailMaker_httpserver main.cpp util/utils.cpp util/utils.h util/addr_ipv4.cpp util/addr_ipv4.h util/log.h net/event_loop.cpp net/event_loop.h net/channel.cpp net/channel.h net/epoller.cpp net/epoller.h net/socket.h net/socket.cpp net/tcp_connection_manager.cpp net/tcp_connection_manager.h net/acceptor.cpp net/acceptor.h net/tcp_connection.cpp net/tcp_connection.h util/callbacks.h net/buffer.h http/http_server.cpp http/http_server.h http/http_response.cpp http/http_response.h http/http_request.cpp http/http_request.h)

target_include_directories(HailMaker_httpserver PUBLIC util net)


#add_executable(test_server test/server.cpp util/utils.cpp util/utils.h util/addr_ipv4.cpp util/addr_ipv4.h util/log.h net/event_loop.cpp net/event_loop.h net/channel.cpp net/channel.h net/epoller.cpp net/epoller.h net/socket.h net/socket.cpp net/tcp_connection_manager.cpp net/tcp_connection_manager.h net/acceptor.cpp net/acceptor.h net/tcp_connection.cpp net/tcp_connection.h)
#target_include_directories(test_server PUBLIC util net)
#
#add_executable(test_client util/utils.cpp util/utils.h util/addr_ipv4.cpp util/addr_ipv4.h util/log.h net/event_loop.cpp net/event_loop.h net/channel.cpp net/channel.h net/epoller.cpp net/epoller.h net/socket.h net/socket.cpp test/client.cpp net/tcp_connection_manager.cpp net/tcp_connection_manager.h net/acceptor.cpp net/acceptor.h net/tcp_connection.cpp net/tcp_connection.h)
#target_include_directories(test_client PUBLIC util net)

enable_testing()

add_executable(
        test_server
        util/utils.cpp
        util/utils.h
        util/addr_ipv4.cpp
        util/addr_ipv4.h
        util/log.h
        net/event_loop.cpp
        net/event_loop.h
        net/channel.cpp
        net/channel.h
        net/epoller.cpp
        net/epoller.h
        net/socket.h
        net/socket.cpp
        net/tcp_connection_manager.cpp
        net/tcp_connection_manager.h
        net/acceptor.cpp
        net/acceptor.h
        net/tcp_connection.cpp
        net/tcp_connection.h
        test/test_channel.cpp
        test/test_tcp_manager_and_connection.cpp util/callbacks.h net/buffer.h test/test_buffer.cpp http/http_server.cpp http/http_server.h http/http_response.cpp http/http_response.h http/http_request.cpp http/http_request.h)

target_link_libraries(
        test_server
        gtest_main
)

target_include_directories(test_server PUBLIC
        util
        net
)

include(GoogleTest)
gtest_discover_tests(test_server)