// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef HAILMAKER_HTTPSERVER_NET_SOCKET_H_
#define HAILMAKER_HTTPSERVER_NET_SOCKET_H_

#include <sys/socket.h>
#include <fcntl.h>
#include <log.h>
#include <assert.h>
#include "addr_ipv4.h"

const int DEFAULT_BACKLOG = 1024;

// a socket fd wrapper
class Socket {
 public:
  Socket();
  explicit Socket(int fd);
  void Bind(AddrIpv4 addr);
  void Listen(int backlog = DEFAULT_BACKLOG);
  Socket Accept(AddrIpv4 *peer_addr);
  void Connect(AddrIpv4 serv_addr);
  void Close();
  void SetNonBlocking();
  void SetReuse();
  size_t Read(char *buf, size_t n);
  size_t Write(char *buf, size_t n);
  inline int GetFd() {
    return fd_;
  }
 private:
  int fd_;
  bool is_passive_;
};

#endif //HAILMAKER_HTTPSERVER_NET_SOCKET_H_
