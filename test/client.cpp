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
  const size_t SIZE = 1024;
  socket_fd.Connect(addr);

  while (true) {
    std::cout << "------------" << std::endl;
    char buf[SIZE];
    scanf("%s", buf);
    auto ret = socket_fd.Write(buf, SIZE);
    if (ret < 0) {
      LOG_FATAL("client write error");
    }
    auto n = socket_fd.Read(buf, SIZE);
    if (n < 0) {
      LOG_FATAL("client read error");
    } else if (n == 0) {
      LOG_INFO("server close the connection");
      break;
    } else {
      LOG_INFO("read from server");
      std::cout << buf << std::endl;
    }
  }
}