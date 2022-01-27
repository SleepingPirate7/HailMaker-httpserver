#include "addr_ipv4.h"
#include "tcp_connection_manager.h"
#include <iostream>

int main() {
  Socket sock;
  sock.Bind(AddrIpv4(6666));
  sock.SetReuse();
  auto fd = epoll_create(5);
  epoll_event event;
  event.events = EPOLLOUT;
  epoll_ctl(fd, EPOLL_CTL_ADD, sock.GetFd(), &event);
  sock.Close();
  epoll_event a[10];
  auto ret = epoll_wait(fd, a, 10, -1);
  if (ret < 0) {
    std::cout << "1";
  } else if (ret == 0) {
    std::cout << "2";
  } else {
    std::cout << "3";
  }
}