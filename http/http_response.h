// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef HAILMAKER_HTTPSERVER_HTTP_HTTP_RESPONSE_H_
#define HAILMAKER_HTTPSERVER_HTTP_HTTP_RESPONSE_H_
#include <string>
#include "http_request.h"

class HttpResponse {
 public:
  HttpResponse(HttpRequest, std::string, std::string, std::string);

  std::string &GetResponse() {
    return response_;
  }
 private:
  std::string response_;
};

#endif //HAILMAKER_HTTPSERVER_HTTP_HTTP_RESPONSE_H_
