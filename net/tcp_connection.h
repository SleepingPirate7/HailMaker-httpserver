// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef HAILMAKER_HTTPSERVER_NET_TCP_CONNECTION_H_
#define HAILMAKER_HTTPSERVER_NET_TCP_CONNECTION_H_

#include "socket.h"
#include "addr_ipv4.h"
class EventLoop;

// TcpConnection's lift time is managed by TcpConnectionManager
class TcpConnection {
 public:
  TcpConnection(uint64_t id,Socket sock,AddrIpv4 addr ,EventLoop *loop);

  void CloseConnection();
 private:
  uint64_t id_;
  Socket sock_;
  AddrIpv4 peer_addr_;
  EventLoop *loop_;

};

#endif //HAILMAKER_HTTPSERVER_NET_TCP_CONNECTION_H_
