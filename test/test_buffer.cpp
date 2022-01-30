// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "buffer.h"
#include <gtest/gtest.h>

TEST(TestBuffer, BasicAssertions) {
  Buffer buf;
  std::string test_data_1("Hello!!!!!");
  buf.Append(test_data_1.data(), test_data_1.size());
  std::string buf_data_1(buf.Peek(), buf.ReadableSize());
  ASSERT_STREQ(test_data_1.data(), buf_data_1.data());
  ASSERT_EQ(buf.ReadableSize(), test_data_1.size());
  buf.Retrieve(10);
  ASSERT_EQ(buf.ReadableSize(), test_data_1.size() - 10);
  buf.RetrieveAll();

  std::string test_data_2;
  for (int i = 0; i < 5; i++) {
    test_data_2.append(test_data_1);
    buf.Append(test_data_1.data(), test_data_1.size());

    std::string buf_data_2(buf.Peek(), buf.ReadableSize());
    // LOG_DEBUG("test_data:%s\n           buf_data :%s\n\n", test_data.data(), buf_data_2.data());
    ASSERT_STREQ(test_data_2.data(), buf_data_2.data());
  }
  ASSERT_EQ(buf.ReadableSize(), test_data_1.size() * 5);
  buf.RetrieveAll();

  Buffer buf_2;
  std::string test_data_3;
  for (int i = 0; i < 2; i++) {
    test_data_3.append(test_data_1);
    buf_2.Append(test_data_1.data(), test_data_1.size());
    std::string buf_data_2(buf_2.Peek(), buf_2.ReadableSize());
    ASSERT_STREQ(test_data_3.data(), buf_data_2.data());
  }

  buf_2.Retrieve(test_data_1.size());
  std::string buf_data(buf_2.Peek(), buf_2.ReadableSize());
  ASSERT_STREQ(test_data_1.data(), buf_data.data());
  buf_2.Append(test_data_1.data(), test_data_1.size());

  std::string test_data_4;
  for (int i = 0; i < 2; i++) {
    test_data_4.append(test_data_1);
  }
  ASSERT_STREQ(test_data_1.data(), buf_data.data());
}