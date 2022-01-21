// Copyright (c) 2022 Wenhao Kong
// https://github.com/WenhaoKong2001
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef HAILMAKER_HTTPSERVER_UTIL_LOG_H_
#define HAILMAKER_HTTPSERVER_UTIL_LOG_H_

//const (
//LOG_FATAL   = LogType(0x1)
//LOG_ERROR   = LogType(0x2)
//LOG_WARNING = LogType(0x4)
//LOG_INFO    = LogType(0x8)
//LOG_DEBUG   = LogType(0x10)
//)

#include <stdio.h>

enum class LOG_LEVEL {
  FATAL, ERROR, WARNING, INFO, DEBUG
};

#define __DEBUG
#ifdef __DEBUG
#define _DEBUG(format, ...) \
              printf(format"\n",##__VA_ARGS__)
#else
#define DEBUG(format, ...)
#endif
#define _LOG_FATAL
#ifdef _LOG_FATAL
#define LOG_FATAL(format, ...) \
                  _DEBUG("\033[0m\033[1;31mLOG_FATAL: \033[0m" format,##__VA_ARGS__)
#else
#define LOG_FATAL(format, ...)
#endif
#define _LOG_ERROR
#ifdef _LOG_ERROR
#define LOG_ERROR(format, ...) \
                  _DEBUG("\033[0m\033[1;33mLOG_ERROR: \033[0m" format,##__VA_ARGS__)
#else
#define LOG_FATAL(format, ...)
#endif
//#define _LOG_WARNING
#ifdef _LOG_WARNING
#define LOG_WARNING(format, ...) \
                  _DEBUG("\033[0m\033[1;33mLOG_WARNING: \033[0m" format,##__VA_ARGS__)
#else
#define LOG_WARNING(format, ...)
#endif
#define _LOG_INFO
#ifdef _LOG_INFO
#define LOG_INFO(format, ...) \
                  _DEBUG("\033[0m\033[1;33mLOG_INFO : \033[0m" format,##__VA_ARGS__)
#else
#define LOG_INFO(format, ...)
#endif
#define _LOG_DEBUG
#ifdef _LOG_DEBUG
#define LOG_DEBUG(format, ...) \
                  _DEBUG("\033[0m\033[1;33mLOG_DEBUG: \033[0m" format,##__VA_ARGS__)
#else
#define LOG_DEBUG(format, ...)
#endif

#endif //HAILMAKER_HTTPSERVER_UTIL_LOG_H_
