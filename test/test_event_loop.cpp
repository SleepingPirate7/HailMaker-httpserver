// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "event_loop.h"

EventLoop *loop;

void thread_func() {
  loop->loop();
}

void test_in__different_thread() {
  EventLoop lp;
  loop = &lp;
  auto thread = std::thread(thread_func);
  thread.join();
}

void test_in_same_thread() {
  EventLoop lp;
  lp.loop();
}

int main() {
  // test_different_in_thread();
  test_in_same_thread();
}