// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef HAILMAKER_HTTPSERVER_UTIL_UTILS_H_
#define HAILMAKER_HTTPSERVER_UTIL_UTILS_H_

#include <arpa/inet.h>
#include "log.h"



uint64_t HostToNet64(uint64_t);
uint16_t HostToNet16(uint16_t);
uint64_t NetToHost64(uint64_t);
uint16_t NetToHost16(uint16_t);

void HostAddrToNet(const char *src,sockaddr_in *dst);


#endif //HAILMAKER_HTTPSERVER_UTIL_UTILS_H_
