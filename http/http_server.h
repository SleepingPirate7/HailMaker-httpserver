// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef HAILMAKER_HTTPSERVER_HTTP_HTTP_SERVER_H_
#define HAILMAKER_HTTPSERVER_HTTP_HTTP_SERVER_H_
#include <memory>
#include <unordered_map>
#include "tcp_connection_manager.h"
#include "http_request.h"

class HttpServer {
 public:
  HttpServer(int thread_num);

  void Start();
  void Handle(const std::string &, std::string);

 private:
  void OnMessageCallback(std::shared_ptr<TcpConnection>, Buffer *input_buffer);
  std::string ReadFileIntoString(std::string);

  std::unordered_map<std::string, std::string> html_context_;
  std::unordered_map<std::string, std::string> url_path_;
  std::unique_ptr<TcpConnectionManager> tcp_manager_;
};

#endif //HAILMAKER_HTTPSERVER_HTTP_HTTP_SERVER_H_
