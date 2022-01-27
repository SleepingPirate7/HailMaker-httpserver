// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef HAILMAKER_HTTPSERVER_NET_BUFFER_H_
#define HAILMAKER_HTTPSERVER_NET_BUFFER_H_

#include <vector>
#include <string>
#include <assert.h>

/*
 * readable = write_index_ - read_index_
 * writeable = size - write_index_
 *
 *  PRE_SIZE           readable            writeable
 * 0---------read index---------write index---------capacity
 */

class Buffer {
 public:
  Buffer() : read_index_(0), write_index_(0) {
  }

  inline const char *Begin() {
    return buf_.data();
  }

  inline size_t WritableSize() {
    return buf_.capacity() - write_index_;
  }

  inline size_t ReadableSize() {
    return write_index_ - read_index_;
  }

  inline size_t PreRead() {
    return read_index_;
  }

  inline const char *Peek() {
    return Begin() + read_index_;
  }

  inline void Retrieve(size_t len) {
    read_index_ += len;
  }

  inline void RetrieveAll() {
    read_index_ = 0;
    write_index_ = 0;
  }

  inline std::string RetrieveAsString() {
    std::string res(Peek(), ReadableSize());
    RetrieveAll();
    return res;
  }

  inline void Append(char *str, size_t len) {
    MakeSpace(len);

  }

  inline void MakeSpace(size_t len) {
    if (WritableSize() < len) {
      if (PreRead() + WritableSize() < len) {
        // need to alloc memory.


      } else {

      }
    }
  }

 private:
  size_t read_index_;
  size_t write_index_;
  std::vector<char> buf_;
};

#endif //HAILMAKER_HTTPSERVER_NET_BUFFER_H_
