
#include <iostream>
#include "addr_ipv4.h"
#include "socket.h"
#include "utils.h"
#include <cstring>

int main() {
  AddrIpv4 addr("127.0.0.1", 6666);
  Socket socket_fd;
  const size_t SIZE = 1024;
  socket_fd.Connect(addr);
  std::string str = "GET /test HTTP/1.1\r\n A:1\r\n\r\nGET /dir2 HTTP/1.1\r\n A:1\r\n\r\n";
  while (true) {
    std::cout << "------------" << std::endl;
    char buf[SIZE];
    scanf("%s", buf);
    auto ret = socket_fd.Write(str.data(), str.size());
    if (ret < 0) {
      LOG_FATAL("client write error");
    }
    memset(buf, 0, sizeof buf);
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