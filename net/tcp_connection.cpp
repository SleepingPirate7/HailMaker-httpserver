// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <cstring>
#include "tcp_connection.h"
#include "tcp_connection_manager.h"

TcpConnection::TcpConnection(uint64_t id, Socket sock, AddrIpv4 addr, EventLoop *loop, TcpConnectionManager *manager)
    : id_(id),
      sock_(sock),
      peer_addr_(addr),
      loop_(loop),
      channel_(loop_, sock_.GetFd()),
      manager_(manager) {
  channel_.SetReadCallBack(std::bind(&TcpConnection::HandleRead, this));
  // channel_.EnableReading();
}

void TcpConnection::CloseConnection() {
  // TODO
  channel_.RemoveFromPoller();
  sock_.Close();
  manager_->DeleteFromMap(id_);
}

void TcpConnection::HandleRead() {
  // TODO
  const int SIZE = 1024;
  char buf[SIZE];
  auto n = sock_.Read(buf, SIZE);
  if (n > 0) {
    LOG_DEBUG("TcpConnection::HandleRead()");
    shared_from_this();
    on_message_callback_(shared_from_this(), buf);
  } else if (n == 0) {
    LOG_DEBUG("client close the connection!");
    CloseConnection();
  } else {
    LOG_FATAL("TcpConnection::HandleRead");
  }
}

void TcpConnection::Send(char *buf) {
  // TODO
  sock_.Write(buf, strlen(buf));
  sock_.Close();
}

void TcpConnection::ConnectionEstablished() {
  // TODO
  channel_.EnableReading();
}



