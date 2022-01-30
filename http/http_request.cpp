// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <regex>
#include "http_request.h"

// We assume that http request doesn't contain request body.
bool HttpRequest::ParseRequest(Buffer *buffer) {
  bool is_more = true;
  bool is_request = false;

  while (is_more) {
    auto line = ParseCRLR(buffer);
    switch (state_) {
      case State::PARSE_LINE:
        if (!ParseLine(line)) {
          return false;
        }
        is_request = true;
        is_more = true;
        state_ = State::PARSE_HEADER;
        break;
      case State::PARSE_HEADER:
        if (line.empty()) {
          is_more = false;
          state_ = State::PARSE_END;
        }
        break;
      case State::PARSE_BODY:
        // TODO PARSE_BODY
        is_more = false;
        break;
      case State::PARSE_END:
        // TODO PARSE_END
        is_more = false;
    }
  }
  return is_request;
}

bool HttpRequest::ParseLine(std::string line) {
  // LOG_DEBUG("%s", line.data());
  std::regex patten("^([^ ]*) ([^ ]*) HTTP/([^ ]*)$");
  std::smatch subMatch;
  if (regex_match(line, subMatch, patten)) {
    method_ = subMatch[1];
    url_ = subMatch[2];
    version_ = subMatch[3];
    state_ = State::PARSE_END;
    // LOG_DEBUG("path:%s", url_.data());
    return true;
  }
  LOG_ERROR("HttpRequest::ParseLine Error");
  return false;
}

std::string HttpRequest::ParseCRLR(Buffer *buffer) {
  static std::string_view CRLR = "\r\n";

  auto end = std::search(buffer->Peek(), buffer->BeginWrite(), CRLR.begin(), CRLR.end());
  if (end == buffer->BeginWrite()) {
    return {};
  }
  std::string str{buffer->Peek(), end};
  buffer->Retrieve(str.size() + 2);
  return str;
}
