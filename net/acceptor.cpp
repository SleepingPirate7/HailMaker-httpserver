// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "acceptor.h"
Acceptor::Acceptor(Socket sock, EventLoop *loop) : listening_socket_(sock),
                                                   channel_(loop, sock.GetFd()) {
  channel_.SetReadCallBack(std::bind(&Acceptor::HandleRead, this));
}

void Acceptor::HandleRead() {
  AddrIpv4 client_addr{};
  auto new_client_sock = listening_socket_.Accept(&client_addr);
  LOG_INFO("accept new client with address is %s", client_addr.ToString().c_str());
  new_conn_callback_(new_client_sock, client_addr);
}

void Acceptor::Listen(AddrIpv4 addr) {
  listening_ = true;
  listening_socket_.Bind(addr);
  listening_socket_.Listen();
  channel_.EnableReading();
}
