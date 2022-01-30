// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef HAILMAKER_HTTPSERVER_HTTP_HTTP_SERVER_H_
#define HAILMAKER_HTTPSERVER_HTTP_HTTP_SERVER_H_
#include <memory>
#include "tcp_connection_manager.h"

class HttpServer {
 public:
  HttpServer(int thread_num);

  void Start();
 private:
  void OnMessageCallback(std::shared_ptr<TcpConnection>,Buffer *input_buffer);

  std::unique_ptr<TcpConnectionManager> tcp_manager_;
};

#endif //HAILMAKER_HTTPSERVER_HTTP_HTTP_SERVER_H_
