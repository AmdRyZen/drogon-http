//
// Created by 神圣·凯莎 on 2022/6/25.
//

#ifndef DROGON_HTTP_LOGINFILTER_H
#define DROGON_HTTP_LOGINFILTER_H

#pragma once
#include "utils/checkloginUtils.h"
#include <drogon/HttpFilter.h>

using namespace drogon;

namespace drogon {
class DROGON_EXPORT LoginFilter final : public HttpFilter<LoginFilter>
{
  public:
    LoginFilter() = default;

    [[gnu::always_inline]] inline void doFilter(const HttpRequestPtr& req,
                  FilterCallback&& fcb,
                  FilterChainCallback&& fccb) override;
};
}  // namespace drogon

void LoginFilter::doFilter(const HttpRequestPtr& req, FilterCallback&& fcb, FilterChainCallback&& fccb)
{
    //Edit your logic here
    if (checkloginUtils::checklogin(req).has_value())
    {
        //Passed
        fccb();
        return;
    }
    //Check failed
    Json::Value data;
    data["msg"] = "NoLogin";
    const auto res = drogon::HttpResponse::newHttpJsonResponse(data);
    res->setStatusCode(k401Unauthorized);
    fcb(res);
}

#endif  // DROGON_HTTP_LOGINFILTER_H
