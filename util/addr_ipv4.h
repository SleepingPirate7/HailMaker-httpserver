// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef HAILMAKER_HTTPSERVER_UTIL_ADDR_IPV4_H_
#define HAILMAKER_HTTPSERVER_UTIL_ADDR_IPV4_H_

#include <string>
#include "utils.h"

class AddrIpv4 {
 public:
  AddrIpv4() = default;
  explicit AddrIpv4(uint16_t port);
  AddrIpv4(const std::string &addr, uint16_t port);

  void SetAddr(const struct sockaddr_in &net_addr);
  const struct sockaddr_in &GetAddr();
  const struct sockaddr *GetStandardAddr();
  size_t GetAddrLen();
 private:
  sockaddr_in addr_;
};


#endif //HAILMAKER_HTTPSERVER_UTIL_ADDR_IPV4_H_
