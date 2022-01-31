// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <regex>
#include <iostream>
#include "http_request.h"

// We assume that http request doesn't contain request body.
bool HttpRequest::ParseRequest(Buffer *buffer) {
  bool has_more = true;
  bool ok = false;

  while (has_more) {
    if (state_ == State::PARSE_LINE) {
      const char *crlf = buffer->FindCRLF();
      if (crlf) {
        ok = ParseLine(buffer->Peek(), crlf);
        if (ok) {
          buffer->RetrieveUntil(crlf + 2);
          state_ = State::PARSE_HEADER;
        } else {
          has_more = false;
        }
      } else {
        has_more = false;
      }
    } else if (state_ == State::PARSE_HEADER) {
      const char *crlf = buffer->FindCRLF();
      if (crlf) {
        const char *colon = std::find(buffer->Peek(), crlf, ':');
        if (colon == crlf) {
          state_ = State::PARSE_END;
          has_more = false;
        }
        buffer->RetrieveUntil(crlf + 2);
      } else {
        has_more = false;
      }

    } else {
      // TODO
    }
  }
  return ok;
}

bool HttpRequest::ParseLine(const char *beg, const char *end) {
  // LOG_DEBUG("%s", line.data());
  std::string line(beg, end);
  std::regex patten("^([^ ]*) ([^ ]*) HTTP/([^ ]*)$");
  std::smatch subMatch;
  if (regex_match(line, subMatch, patten)) {
    method_ = subMatch[1];
    url_ = subMatch[2];
    version_ = subMatch[3];
    // state_ = State::PARSE_END;
    // LOG_DEBUG("path:%s", url_.data());
    return true;
  }
  LOG_ERROR("HttpRequest::ParseLine Error");
  return false;
}

bool HttpRequest::GotAll() {
  return state_ == State::PARSE_END;
}
