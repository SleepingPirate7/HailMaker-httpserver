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
#include "CallBacks.h"
#include "addr_ipv4.h"
#include "channel.h"

class EventLoop;
class TcpConnectionManager;

// TcpConnection's lift time is managed by TcpConnectionManager
class TcpConnection : public std::enable_shared_from_this<TcpConnection> {
 public:
  enum TcpConnectionStatue { Connecting, Connected, Closing, Closed, };

  TcpConnection(uint64_t id, Socket sock, AddrIpv4 addr, EventLoop *loop, TcpConnectionManager *manager);

  void CloseConnection();
  void Send(char *);

  inline void SetOnMessageCallback(OnMessageCallBack cb) {
    on_message_callback_ = std::move(cb);
  }

  // This function is only called once when a new connection is established.
  void ConnectionEstablished();
 private:
  void HandleRead();
  void HandleWrite();
  void HandleCLose();
  uint64_t id_;
  Socket sock_;
  AddrIpv4 peer_addr_;
  EventLoop *loop_;
  Channel channel_;
  std::string output_buf_;
  std::string input_buf_;
  OnMessageCallBack on_message_callback_;
  TcpConnectionStatue statue_;
  TcpConnectionManager *manager_;
};

#endif //HAILMAKER_HTTPSERVER_NET_TCP_CONNECTION_H_
