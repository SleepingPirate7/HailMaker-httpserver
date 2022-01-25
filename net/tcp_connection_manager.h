// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef HAILMAKER_HTTPSERVER_NET_TCP_CONNECTION_MANAGER_H_
#define HAILMAKER_HTTPSERVER_NET_TCP_CONNECTION_MANAGER_H_

#include <memory>
#include <unordered_map>
#include <utility>
#include "acceptor.h"
#include "event_loop.h"
#include "tcp_connection.h"

class TcpConnectionManager {
 public:
  using CallBack = std::function<void(char *)>;

  TcpConnectionManager();
  ~TcpConnectionManager();

  void Start(AddrIpv4 addr);

  inline void SetOnMessageCallback(CallBack cb) {
    on_message_callback_ = std::move(cb);
  }
 private:
  using ConnectionMap = std::unordered_map<uint64_t, std::shared_ptr<TcpConnection>>;
  void NewConnection(Socket sock, AddrIpv4 addr);

  EventLoop *reactor_;
  Acceptor acceptor_;
  ConnectionMap conn_map_;
  uint64_t next_conn_id_;
  CallBack on_message_callback_;
};

#endif //HAILMAKER_HTTPSERVER_NET_TCP_CONNECTION_MANAGER_H_
