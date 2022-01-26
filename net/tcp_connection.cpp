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
  channel_.SetWriteCallBack(std::bind(&TcpConnection::HandleWrite, this));
  // channel_.EnableReading();
}

void TcpConnection::CloseConnection() {
  // TODO
  if (output_buf_.empty()) {
    channel_.RemoveFromPoller();
    sock_.Close();
    manager_->DeleteFromMap(id_);
  } else {
    statue_ = TcpConnectionStatue::Closing;
  }
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
  if (output_buf_.empty() && !channel_.IsWriting()) {
    auto len = strlen(buf);
    auto ret = sock_.Write(buf, len);
    if (ret > 0) {
      if (ret < len) {
        input_buf_.append(buf + ret, len - ret);
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
          if (!channel_.IsWriting()) {
            channel_.EnableWriting();
          }
        }
      }
    } else if (ret == 0) {
      // client close the connection
      CloseConnection();
    } else {
      // send buf of TCP is full registering POLLOUT event and waiting for it.
      if (errno == EAGAIN || errno == EWOULDBLOCK) {
        if (!channel_.IsWriting()) {
          channel_.EnableWriting();
        }
      } else {
        // some error happened.Simply close the connection.
        CloseConnection();
      }
    }
  }
}

void TcpConnection::HandleWrite() {

}

void TcpConnection::ConnectionEstablished() {
  // TODO
  channel_.EnableReading();
  statue_ = Connected;
}

void TcpConnection::HandleCLose() {

}





