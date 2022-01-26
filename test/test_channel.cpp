// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <gtest/gtest.h>
#include "channel.h"
#include "event_loop.h"
#include "socket.h"

TEST(TestChannel, BasicAssertions) {
  EventLoop loop;
  Socket sock;
  Channel chan(&loop, sock.GetFd());
  ASSERT_EQ(chan.GetChannelStatus(), Channel::ChannelStatus::DELETED);
  chan.EnableReading();
  ASSERT_EQ(chan.GetChannelStatus(), Channel::ChannelStatus::POLLING);
  chan.EnableWriting();
  ASSERT_EQ(chan.IsWriting(), true);
  chan.DisableReadingAndWriting();
  ASSERT_EQ(chan.IsWriting(), false);
  chan.RemoveFromPoller();
  ASSERT_EQ(chan.GetChannelStatus(), Channel::ChannelStatus::DELETED);
}


