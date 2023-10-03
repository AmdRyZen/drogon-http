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
class DROGON_EXPORT LoginFilter : public HttpFilter<LoginFilter>
{
  public:
    LoginFilter() = default;

    void doFilter(const HttpRequestPtr& req,
                  FilterCallback&& fcb,
                  FilterChainCallback&& fccb) override;
};
}  // namespace drogon

void LoginFilter::doFilter(const HttpRequestPtr& req, FilterCallback&& fcb, FilterChainCallback&& fccb)
{
    auto user_id = checkloginUtils::checklogin(req);
    //Edit your logic here
    if (user_id.has_value())
    {
        //Passed
        fccb();
        return;
    }
    //Check failed
    Json::Value data;
    data["msg"] = "NoLogin";
    auto res = drogon::HttpResponse::newHttpJsonResponse(data);
    res->setStatusCode(k401Unauthorized);
    fcb(res);
}

#endif  // DROGON_HTTP_LOGINFILTER_H
