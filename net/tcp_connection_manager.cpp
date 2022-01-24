// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "tcp_connection_manager.h"

TcpConnectionManager::TcpConnectionManager() : reactor_(new EventLoop),
                                               acceptor_(Socket(), reactor_) {
  acceptor_.SetConnCallback(std::bind(&TcpConnectionManager::NetConnection,
                                      this,
                                      std::placeholders::_1,
                                      std::placeholders::_2));
}

void TcpConnectionManager::NetConnection(Socket sock, AddrIpv4 addr) {

  sock.Close();
}

void TcpConnectionManager::Start(AddrIpv4 addr) {
  acceptor_.Listen(addr);
  reactor_->loop();
}
