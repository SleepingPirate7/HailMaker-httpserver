// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef HAILMAKER_HTTPSERVER_NET_TCP_CONNECTION_MANAGER_H_
#define HAILMAKER_HTTPSERVER_NET_TCP_CONNECTION_MANAGER_H_

#include <unordered_map>
#include "acceptor.h"
#include "event_loop.h"

class TcpConnectionManager {
 public:
  TcpConnectionManager();

  void Start(AddrIpv4 addr);
 private:
  void NetConnection(Socket sock, AddrIpv4 addr);

  EventLoop *reactor_;
  Acceptor acceptor_;
  uint64_t next_conn_id_;

};

#endif //HAILMAKER_HTTPSERVER_NET_TCP_CONNECTION_MANAGER_H_
