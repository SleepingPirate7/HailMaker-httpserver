// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef HAILMAKER_HTTPSERVER_HTTP_HTTP_REQUEST_H_
#define HAILMAKER_HTTPSERVER_HTTP_HTTP_REQUEST_H_

#include <string>
#include "http_server.h"

class HttpRequest {
 public:
  enum class State { PARSE_LINE, PARSE_HEADER, PARSE_BODY, PARSE_END };

  HttpRequest() = default;

  bool ParseRequest(Buffer *buffer);
  bool ParseLine(std::string);

  inline std::string GetMethod() {
    return method_;
  }

  inline std::string GetUrl() {
    return url_;
  }

  inline std::string GetVersion_() {
    return version_;
  }
 private:
  std::string ParseCRLR(Buffer *);

  std::string method_;
  std::string url_;
  std::string version_;
  State state_{State::PARSE_LINE};
};

#endif //HAILMAKER_HTTPSERVER_HTTP_HTTP_REQUEST_H_
