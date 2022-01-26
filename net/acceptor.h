// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef HAILMAKER_HTTPSERVER_NET_ACCEPTOR_H_
#define HAILMAKER_HTTPSERVER_NET_ACCEPTOR_H_

#include <utility>

#include "log.h"
#include "channel.h"
#include "socket.h"
#include "CallBacks.h"

class Acceptor {
 public:

  Acceptor(Socket sock, EventLoop *loop);

  inline void SetConnCallback(NewConCallBack cb) {
    new_conn_callback_ = std::move(cb);
  }

  void Listen(AddrIpv4 addr);
 private:
  void HandleRead();
  Socket listening_socket_;
  Channel channel_;
  NewConCallBack new_conn_callback_;
  bool listening_;
};

#endif //HAILMAKER_HTTPSERVER_NET_ACCEPTOR_H_
