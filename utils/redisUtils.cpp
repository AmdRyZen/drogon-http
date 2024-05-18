//
// Created by 天使之王·彦 on 2022/1/4.
//
#include "redisUtils.h"
#include <drogon/drogon.h>
#include <memory>

std::optional<std::string> redisUtils::getRedisValue(const std::string& command)
{
    std::mutex mutex;
    std::unique_lock<std::mutex> lock(mutex);
    std::condition_variable commandFinished;
    std::optional<std::string> result;

    const auto redisClient = drogon::app().getFastRedisClient();
    redisClient->execCommandAsync(
        [&](const drogon::nosql::RedisResult& r) {
            if (!r.isNil())
                result = r.asString();

            commandFinished.notify_all();
        },
        [&](const std::exception& e) {
            result = std::nullopt;
        },
        command);

    commandFinished.wait(lock);

    return result;
}

drogon::Task<std::string> redisUtils::getCoroRedisValue(const std::string& command)
{
    const auto redisClient = drogon::app().getFastRedisClient();
    const auto data = co_await redisClient->execCommandCoro(command);
    if (data.isNil())
    {
        co_return "";
    }
    co_return data.asString();
}
