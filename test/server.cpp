// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <iostream>
#include "event_loop.h"
#include "addr_ipv4.h"
#include "socket.h"
#include "utils.h"

int main() {
  AddrIpv4 addr("127.0.0.1", 6666);
  Socket socket_fd;
  socket_fd.Bind(addr);
  socket_fd.Listen();
  const size_t SIZE = 1024;
  AddrIpv4 client_addr{};
  auto client_fd = socket_fd.Accept(&client_addr);
  LOG_INFO("accept new connection");
  while (true) {
    char buf[SIZE];
    std::cout << "+++++" << std::endl;
    auto n = client_fd.Read(buf, SIZE);
    if (n < 0) {
      LOG_FATAL("server read error");
    } else if (n == 0) {
      LOG_INFO("client closes the connection");
      break;
    } else {
      LOG_INFO("read from client");
      std::cout << buf << std::endl;
      client_fd.Write(buf, SIZE);
    }
  }
}