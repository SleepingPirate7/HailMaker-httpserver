// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef HAILMAKER_HTTPSERVER_NET_EVENT_LOOP_H_
#define HAILMAKER_HTTPSERVER_NET_EVENT_LOOP_H_

#include <thread>
#include <memory>
#include "log.h"

class Channel;
class Epoller;

class EventLoop {
 public:
  EventLoop();
  ~EventLoop();
  void loop();
  void UpdateChannel(Channel *);
 private:
  bool exit_;
  bool looping_;
  std::unique_ptr<Epoller> poller_;
};

#endif //HAILMAKER_HTTPSERVER_NET_EVENT_LOOP_H_
