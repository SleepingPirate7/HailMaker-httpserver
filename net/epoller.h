// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef HAILMAKER_HTTPSERVER_NET_EPOLLER_H_
#define HAILMAKER_HTTPSERVER_NET_EPOLLER_H_

#include <sys/epoll.h>
#include <vector>
#include "log.h"

class Channel;

const int MAX_EVENTS = 1024;

class Epoller {
 public:
  Epoller();
  ~Epoller();
  std::vector<Channel *> Poll();
  void UpdateChannel(Channel *);
  void RemoveFromChannel(Channel *);
 private:
  int epoll_fd_;
  struct epoll_event *events_;
};

#endif //HAILMAKER_HTTPSERVER_NET_EPOLLER_H_
