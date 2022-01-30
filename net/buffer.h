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
#include <sys/uio.h>
#include "log.h"

/*
 * readable = write_index_ - read_index_
 * writeable = size - write_index_
 *
 *  PRE_SIZE           readable            writeable
 * 0---------read index---------write index---------capacity
 */

class Buffer {
 public:
  const int InitialSize = 1024;
  Buffer() : read_index_(0), write_index_(0), buf_(InitialSize) {}

  inline char *Begin() {
    return buf_.data();
  }

  inline size_t WritableSize() {
    return buf_.size() - write_index_;
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

  inline const char *BeginWrite() {
    return Begin() + write_index_;
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

  inline std::string_view RetrieveStringView() {
    std::string_view res(Peek(), ReadableSize());
    return res;
  }

  inline void Append(char *str, size_t len) {
    MakeSpace(len);
    std::copy(str, str + len, Begin() + write_index_);
    write_index_ += len;
  }

  inline bool Empty() {
    return read_index_ == write_index_;
  }

  size_t ReadFd(int fd) {
    char extrabuf[65536];
    struct iovec vec[2];
    const size_t writable = WritableSize();
    vec[0].iov_base = Begin() + write_index_;
    vec[0].iov_len = writable;
    vec[1].iov_base = extrabuf;
    vec[1].iov_len = sizeof extrabuf;

    const size_t n = readv(fd, vec, 2);
    if (n < 0) {
      // TODO what should we do??
      // *savedErrno = errno;
      LOG_WARNING("ReadFd error!");
    } else if (n <= writable) {
      write_index_ += n;
    } else {
      write_index_ = buf_.size();
      Append(extrabuf, n - writable);
    }
    return n;
  }

  void swap(Buffer &buf) {
    buf_.swap(buf.buf_);
    std::swap(read_index_, buf.read_index_);
    std::swap(write_index_, buf.write_index_);
  }
 private:

  inline void MakeSpace(size_t len) {
    if (WritableSize() < len) {
      if (PreRead() + WritableSize() < len) {
        // need to alloc memory.
        // LOG_DEBUG("buffer resize:%lu", write_index_ + len);
        buf_.resize(write_index_ + len);
      } else {
        auto readable = ReadableSize();
        std::copy(Begin() + read_index_, Begin() + write_index_, Begin());
        read_index_ = 0;
        write_index_ = read_index_ + readable;
      }
    }
  }

  size_t read_index_;
  size_t write_index_;
  std::vector<char> buf_;
};

#endif //HAILMAKER_HTTPSERVER_NET_BUFFER_H_
