// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "http_response.h"
static const std::string version_ = "HTTP/1.1";
static const std::string ok_ = "OK";
static const std::string sp = " ";
static const std::string CRLF = "\r\n";
HttpResponse::HttpResponse(HttpRequest req, std::string statue_code, std::string statue, std::string context) {
  response_.append(version_);
  response_.append(sp);
  response_.append(statue_code);
  response_.append(sp);
  response_.append(statue);
  response_.append(CRLF);
  response_.append(CRLF);
  response_.append(context);
}


