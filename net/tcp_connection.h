// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef HAILMAKER_HTTPSERVER_NET_TCP_CONNECTION_H_
#define HAILMAKER_HTTPSERVER_NET_TCP_CONNECTION_H_

#include <memory>
#include <utility>
#include "socket.h"
#include "addr_ipv4.h"
#include "channel.h"
class EventLoop;

// TcpConnection's lift time is managed by TcpConnectionManager
class TcpConnection : public std::enable_shared_from_this<TcpConnection> {
 public:
  using CallBack = std::function<void(std::shared_ptr<TcpConnection>, char *)>;

  TcpConnection(uint64_t id, Socket sock, AddrIpv4 addr, EventLoop *loop);

  void CloseConnection();
  void Send(char *);

  inline void SetOnMessageCallback(CallBack cb) {
    on_message_callback_ = std::move(cb);
  }

  // This function is only called once when a new connection is established.
  void ConnectionEstablished();
 private:
  void HandleRead();

  uint64_t id_;
  Socket sock_;
  AddrIpv4 peer_addr_;
  EventLoop *loop_;
  Channel channel_;
  CallBack on_message_callback_;
};

#endif //HAILMAKER_HTTPSERVER_NET_TCP_CONNECTION_H_
