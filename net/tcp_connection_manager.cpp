// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "tcp_connection_manager.h"
#include "tcp_connection.h"

TcpConnectionManager::TcpConnectionManager(int thread_num) : reactor_(new EventLoop),
                                                             acceptor_(Socket(), reactor_),
                                                             thread_num_(thread_num) {
  acceptor_.SetConnCallback(std::bind(&TcpConnectionManager::NewConnection,
                                      this,
                                      std::placeholders::_1,
                                      std::placeholders::_2));

  for (int i = 0; i < thread_num_; i++) {
    sub_reactors_.push_back(new EventLoop);
  }

  for (int i = 0; i < thread_num_; i++) {
    auto func = std::bind(&EventLoop::loop, sub_reactors_[i]);
    loop_threads_.emplace_back(std::thread(func));
  }

  for (int i = 0; i < thread_num_ * 2; i++) {
    std::cout << GetNextLoopId() << " ";
  }
}

void TcpConnectionManager::NewConnection(Socket client_sock, AddrIpv4 addr) {
  // TODO support multithreading.
  auto next = GetNextLoopId();
  auto reactor = sub_reactors_[next];
  // TODO
  auto conn = std::make_shared<TcpConnection>(next_conn_id_,
                                              client_sock,
                                              addr,
                                              reactor, this, next);

  // FIXME Is this necessary?
  conn->SetOnMessageCallback(on_message_callback_);

  conn_map_[next_conn_id_] = conn;
  next_conn_id_++;

  // TODO add on connection callback used by upper user(e.g http manager) for further work.
  // e.g http manager will use this callback to establish a new http connection.
  // TODO (update) Do we really need this?
  // on_connection_callback_(conn);

  conn->ConnectionEstablished();
}

void TcpConnectionManager::Start(AddrIpv4 addr) {
  acceptor_.Listen(addr);
  reactor_->loop();
}

TcpConnectionManager::~TcpConnectionManager() {
  delete reactor_;
  for (int i = 0; i < thread_num_; i++) {
    delete sub_reactors_[i];
    loop_threads_[i].join();
  }
}

void TcpConnectionManager::DeleteFromMap(uint64_t id) {
  std::scoped_lock lock_guard(mu_);
  conn_map_.erase(id);
}

int TcpConnectionManager::GetNextLoopId() const {
  static int idx = 0;
  if (idx < thread_num_) {
    return idx++;
  } else {
    idx = 0;
    return idx++;
  }
}
