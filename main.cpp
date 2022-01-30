#include "addr_ipv4.h"
#include "tcp_connection_manager.h"
#include <iostream>
#include "unordered_map"
#include "http/http_server.h"
#include "http/http_request.h"

int main() {
  HttpServer server(1);
  server.Handle("/test", "/test/test");
  HttpRequest request;
  Buffer buf;
  std::string req = "GET /dir HTTP/1.1\r\n A:1\r\n\r\nGET /dir2 HTTP/1.1\r\n A:1\r\n\r\n";
  buf.Append(req.data(), req.size());

  if (request.ParseRequest(&buf)) {
    std::cout << request.GetMethod() << " " << request.GetUrl() << std::endl;
  }

  HttpRequest request2;
  if (request2.ParseRequest(&buf)) {
    std::cout << request2.GetMethod() << " " << request2.GetUrl() << std::endl;
  }

  auto str = server.ReadFileIntoString("../test.html");
  std::cout << str;
}