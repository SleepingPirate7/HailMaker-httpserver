// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "http_server.h"
#include <functional>
using std::placeholders::_1;
using std::placeholders::_2;

HttpServer::HttpServer(int thread_num) : tcp_manager_(new TcpConnectionManager(thread_num)) {
  tcp_manager_->SetOnMessageCallback(std::bind(&HttpServer::OnMessageCallback, this, _1, _2));
}

void HttpServer::OnMessageCallback(std::shared_ptr<TcpConnection> conn, Buffer *input_buffer) {
  auto str = input_buffer->RetrieveAsString();
  LOG_INFO("Receive from client:%s", str.data());
  conn->Send(str.data(), str.size());
}

void HttpServer::Start() {
  tcp_manager_->Start(AddrIpv4(6666));
}
