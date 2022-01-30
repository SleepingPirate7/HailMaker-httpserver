// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "http_server.h"
#include <functional>
#include <utility>
#include <fstream>
#include <sstream>
using std::placeholders::_1;
using std::placeholders::_2;

HttpServer::HttpServer(int thread_num) : tcp_manager_(new TcpConnectionManager(thread_num)) {
  tcp_manager_->SetOnMessageCallback(std::bind(&HttpServer::OnMessageCallback, this, _1, _2));
}

void HttpServer::OnMessageCallback(std::shared_ptr<TcpConnection> conn, Buffer *input_buffer) {
  // auto str = input_buffer->RetrieveAsString();
  // LOG_INFO("Receive from client:%s", str.data());
  // conn->Send(str.data(), str.size());
  HttpRequest request;
  if (request.ParseRequest(input_buffer)) {

  } else {

  }
}

void HttpServer::Start() {
  tcp_manager_->Start(AddrIpv4(6666));
  for (auto &path : url_path_) {
    auto html = ReadFileIntoString(path.second);
    if (html.empty()) {
      LOG_FATAL("HttpServer::Start()  File doesn't exist.");
    }
    html_context_[path.second] = html;
  }
}

void HttpServer::Handle(const std::string &url, std::string path) {
  url_path_[url] = std::move(path);
}

std::string HttpServer::ReadFileIntoString(std::string filename) {
  std::FILE *fp = std::fopen(filename.data(), "rb");
  if (fp) {
    std::string contents;
    std::fseek(fp, 0, SEEK_END);
    contents.resize(std::ftell(fp));
    std::rewind(fp);
    std::fread(&contents[0], 1, contents.size(), fp);
    std::fclose(fp);
    return (contents);
  }
  throw (errno);
}

