//
// Created by 天使之王·彦 on 2022/1/4.
//

#ifndef DROGON_HTTP_REDISUTILS_H
#define DROGON_HTTP_REDISUTILS_H

#include <optional>
#include <string>
#include <drogon/drogon.h>

class redisUtils
{
  public:
    static std::optional<std::string> getRedisValue(const std::string& command);

    static drogon::Task<std::string> getCoroRedisValue(const std::string& command);
};

#endif  //DROGON_HTTP_REDISUTILS_H
