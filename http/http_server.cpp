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
#include <iostream>

#include "http_response.h"
using std::placeholders::_1;
using std::placeholders::_2;

HttpServer::HttpServer(int thread_num) : tcp_manager_(new TcpConnectionManager(thread_num)) {
  tcp_manager_->SetOnMessageCallback(std::bind(&HttpServer::OnMessageCallback, this, _1, _2));
}

void HttpServer::OnMessageCallback(std::shared_ptr<TcpConnection> conn, Buffer *input_buffer) {
  HttpRequest request;
  if (request.ParseRequest(input_buffer)) {
    if (request.GotAll()) {
      if (request.GetMethod() == "GET") {
        if (url_path_.count(request.GetUrl())) {
          auto context = html_context_[url_path_[request.GetUrl()]];
          HttpResponse resp(request, "200", "OK", context);
          conn->Send(resp.GetResponse().data(), resp.GetResponse().size());
        } else {
          auto context = html_context_["404"];
          HttpResponse resp(request, "404", "NOT FOUND", context);
          conn->Send(resp.GetResponse().data(), resp.GetResponse().size());
        }
        conn->CloseConnection();
      } else {
        // TODO
        std::string context = "HTTP/1.1 400 Bad Request\r\n\r\n";
        conn->Send(context.data(), context.size());
        conn->CloseConnection();
      }
    }
  } else {
    // TODO bad request
  }
}

void HttpServer::Start() {
  for (auto &path : url_path_) {
    auto html = ReadFileIntoString(path.second);
    if (html.empty()) {
      LOG_FATAL("HttpServer::Start()  File doesn't exist.");
    }
    html_context_[path.second] = html;
  }
  auto html = ReadFileIntoString("../recourse/404.html");
  html_context_["404"] = html;
  tcp_manager_->Start(AddrIpv4(80));
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
  LOG_FATAL("HttpServer::ReadFileIntoString()");
}

