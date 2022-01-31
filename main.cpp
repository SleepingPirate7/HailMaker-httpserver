#include "addr_ipv4.h"
#include "tcp_connection_manager.h"
#include <iostream>
#include "unordered_map"
#include "http/http_server.h"
#include "http/http_request.h"

int main() {
  HttpServer server(1);
  server.Handle("/hello", "../recourse/hello.html");
  server.Start();
}