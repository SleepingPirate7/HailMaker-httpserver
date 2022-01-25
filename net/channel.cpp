// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "channel.h"
#include "event_loop.h"

Channel::Channel(EventLoop *loop, int fd) : loop_(loop),
                                            status_(ChannelStatus::DELETED),
                                            fd_(fd),
                                            events_(0),
                                            revent_(0) {
}

void Channel::Update() {
  loop_->UpdateChannel(this);
}

void Channel::RemoveFromPoller() {

}

void Channel::HandleEvent() {
  handling_event_ = true;
  LOG_DEBUG("HandleEvent");
  if (revent_ & EPOLLIN) {
    if (read_callback_)read_callback_();
  }
  if (revent_ & EPOLLOUT) {
    if (write_callback_)write_callback_();
  }
  handling_event_ = false;
}
