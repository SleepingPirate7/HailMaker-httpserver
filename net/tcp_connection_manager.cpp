// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "tcp_connection_manager.h"
#include "tcp_connection.h"

TcpConnectionManager::TcpConnectionManager() : reactor_(new EventLoop),
                                               acceptor_(Socket(), reactor_) {
  acceptor_.SetConnCallback(std::bind(&TcpConnectionManager::NewConnection,
                                      this,
                                      std::placeholders::_1,
                                      std::placeholders::_2));
}

void TcpConnectionManager::NewConnection(Socket client_sock, AddrIpv4 addr) {
  // TODO
  auto conn = std::make_shared<TcpConnection>(next_conn_id_,
                                              client_sock,
                                              addr,
                                              reactor_, this);

  // FIXME simple test now.Will be set a real on message callback by upper user.
  conn->SetOnMessageCallback([](const std::shared_ptr<TcpConnection> conn, char *buf) {
    LOG_INFO("Message from client:%s", buf);
    conn->Send(buf);
  });

  conn_map_[next_conn_id_] = conn;
  next_conn_id_++;
  conn->ConnectionEstablished();
}

void TcpConnectionManager::Start(AddrIpv4 addr) {
  acceptor_.Listen(addr);
  reactor_->loop();
}

TcpConnectionManager::~TcpConnectionManager() {
  delete reactor_;
}

void TcpConnectionManager::DeleteFromMap(uint64_t id) {
  std::scoped_lock lock_guard(mu_);
  if (conn_map_.count(id)) {
    conn_map_.erase(id);
  }
}
