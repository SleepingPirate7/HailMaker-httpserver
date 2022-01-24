#include "addr_ipv4.h"
#include "tcp_connection_manager.h"
#include <iostream>

int main() {
  AddrIpv4 addr("127.0.0.1", 6666);
  TcpConnectionManager server;
  server.Start(addr);

}