// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef HAILMAKER_HTTPSERVER_UTIL_CALLBACKS_H_
#define HAILMAKER_HTTPSERVER_UTIL_CALLBACKS_H_
#include <functional>
#include <addr_ipv4.h>
#include <socket.h>
#include <memory>
#include "buffer.h"

class TcpConnection;

using NewConCallBack = std::function<void(Socket, AddrIpv4)>;
using OnMessageCallBack = std::function<void(std::shared_ptr<TcpConnection>, Buffer *)>;
using OnConnectionCallBack = std::function<void(std::shared_ptr<TcpConnection>)>;

#endif //HAILMAKER_HTTPSERVER_UTIL_CALLBACKS_H_
