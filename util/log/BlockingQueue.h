// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef HAILMAKER_HTTPSERVER_UTIL_LOG_BLOCKINGQUEUE_H_
#define HAILMAKER_HTTPSERVER_UTIL_LOG_BLOCKINGQUEUE_H_

#include <deque>
#include <mutex>
#include <condition_variable>

template<typename T>
class BlockingQueue {
 public:
  using QueueT = std::deque<T>;

  void Put(const T &val) {
    std::unique_lock lock_guard(mu_);
    queue_.push_back(val);
    cv_.notify_one();
  }

  void Put(T &&val) {
    std::unique_lock lock_guard(mu_);
    queue_.push_back(std::move(val));
    cv_.notify_one();
  }

  T Take() {
    std::unique_lock lock_guard(mu_);
    while (queue_.empty()) {
      cv_.wait(lock_guard);
    }
    auto front = std::move(queue_.front());
    queue_.pop_front();
    return front;
  }

  QueueT TakeAll() {
    QueueT new_queue;
    {
      std::unique_lock lock_guard(mu_);
      new_queue = std::move(queue_);
    }
    return new_queue;
  }

  size_t Size() {
    std::unique_lock lock_guard(mu_);
    return queue_.size();
  }

 private:
  std::mutex mu_;
  std::condition_variable cv_;
  QueueT queue_;
};

#endif //HAILMAKER_HTTPSERVER_UTIL_LOG_BLOCKINGQUEUE_H_
