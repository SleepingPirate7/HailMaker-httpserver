// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "socket.h"
#include <unistd.h>

Socket::Socket() : is_passive_(true) {
  fd_ = socket(AF_INET, SOCK_STREAM, 0);
}

Socket::Socket(int fd) : fd_(fd), is_passive_(true) {
}

void Socket::SetNonBlocking() {
  assert(fd_ != 0);
  auto old_option = ::fcntl(fd_, F_GETFL);
  auto new_option = old_option | O_NONBLOCK | O_CLOEXEC;
  ::fcntl(fd_, F_SETFL, new_option);
}

void Socket::Bind(AddrIpv4 addr) {
  assert(fd_ != 0);
  auto ret = ::bind(fd_, addr.GetStandardAddr(), addr.GetAddrLen());
  if (ret < 0) {
    LOG_FATAL("Socket::Bind error");
  }
  is_passive_ = false;
}

void Socket::Listen(int backlog) {
  assert(fd_ != 0);
  if (!is_passive_) {
    auto ret = ::listen(fd_, backlog);
    if (ret < 0) {
      LOG_FATAL("Socket::Listen error");
    }
  }
}

Socket Socket::Accept(AddrIpv4 *peer_addr) {
  assert(fd_ != 0);
  AddrIpv4 client_addr{};
  struct sockaddr_in client{};
  socklen_t client_len = sizeof(client);
  auto client_fd = ::accept(fd_, (struct sockaddr *) &client, &client_len);
  if (client_fd < 0) {
    LOG_FATAL("Socket::Accept error");
  }
  client_addr.SetAddr(client);
  *peer_addr = client_addr;
  return Socket(client_fd);
}

void Socket::Connect(AddrIpv4 serv_addr) {
  assert(fd_ != 0);
  auto ret = ::connect(fd_, serv_addr.GetStandardAddr(), serv_addr.GetAddrLen());
  if (ret < 0) {
    LOG_FATAL("Socket::Connect error");
  }
}

void Socket::Close() {
  assert(fd_ != 0);
  ::close(fd_);
}

size_t Socket::Read(char *buf, size_t n) {
  return ::read(fd_, buf, n);
}

size_t Socket::Write(char *buf, size_t n) {
  return ::write(fd_, buf, n);
}

void Socket::SetReuse() {
  assert(fd_ != 0);
  int reuse = 1;
  setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
}


