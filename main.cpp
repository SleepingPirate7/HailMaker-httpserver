#include <iostream>
#include <thread>
#include <vector>
#include "util/log/BlockingQueue.h"

int main() {
  BlockingQueue<int> que;
  std::vector<std::thread> thread_vec;
  for (int i = 0; i < 10; i++) {
    thread_vec.emplace_back([&que, i]() {
      que.Put(i);
    });
  }

  for (auto &iter : thread_vec){
    iter.join();
  }

  while (que.Size()) {
    std::cout << que.Take() << std::endl;
  }

  return 0;
}
