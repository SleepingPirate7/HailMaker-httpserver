// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "event_loop.h"
#include <assert.h>
#include <algorithm>
#include "epoller.h"
#include "channel.h"

EventLoop::EventLoop() : looping_(false), poller_(new Epoller) {
}

void EventLoop::loop() {
  assert(!looping_);
  looping_ = true;
  while (!exit_) {
    auto events = poller_->Poll();
    for (auto &iter : events) {
      iter->HandleEvent();
    }
  }
  LOG_DEBUG("event loop exit");
  looping_ = false;
}

EventLoop::~EventLoop() {
  assert(!looping_);
}

void EventLoop::UpdateChannel(Channel *channel) {
  poller_->UpdateChannel(channel);
}

void EventLoop::RemoveFromChannel(Channel *channel) {
  poller_->RemoveFromChannel(channel);
}

