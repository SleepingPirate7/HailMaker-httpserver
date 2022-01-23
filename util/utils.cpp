// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT


#include <cstdlib>
#include "utils.h"


uint64_t HostToNet64(uint64_t host) {
  return htonl(host);
}

uint16_t HostToNet16(uint16_t host) {
  return htons(host);
}

uint64_t NetToHost64(uint64_t net) {
  return ntohl(net);
}

uint16_t NetToHost16(uint16_t net) {
  return ntohs(net);
}

void HostAddrToNet(const char *src, struct sockaddr_in *dst) {
  if (inet_pton(AF_INET, src, &dst->sin_addr) == 0) {
    LOG_FATAL("sockets::HostAddrToNet error");
    exit(1);
  }
}
