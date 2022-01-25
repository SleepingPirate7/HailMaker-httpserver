// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "tcp_connection.h"

TcpConnection::TcpConnection(uint64_t id, Socket sock, AddrIpv4 addr, EventLoop *loop)
    : id_(id), sock_(sock), peer_addr_(addr), loop_(loop) {
}

void TcpConnection::CloseConnection() {
  // TODO
  sock_.Close();
}

