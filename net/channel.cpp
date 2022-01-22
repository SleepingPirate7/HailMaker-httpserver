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

}
