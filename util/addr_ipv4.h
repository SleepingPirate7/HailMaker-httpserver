// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef HAILMAKER_HTTPSERVER_UTIL_ADDR_IPV4_H_
#define HAILMAKER_HTTPSERVER_UTIL_ADDR_IPV4_H_

#include <string>
#include "utils.h"
namespace hailmaker {
class AddrIpv4 {
 public:
  explicit AddrIpv4(uint16_t port);
  AddrIpv4(const std::string &addr, uint16_t port);

  void SetAddr(const struct sockaddr_in &net_addr);
  const struct sockaddr_in& GetAddr();
  void GetStandardAddr();
 private:
  sockaddr_in addr_;
};
} // namespace hailmaker

#endif //HAILMAKER_HTTPSERVER_UTIL_ADDR_IPV4_H_
