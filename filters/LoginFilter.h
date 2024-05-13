//
// Created by 神圣·凯莎 on 2022/6/25.
//

#ifndef DROGON_HTTP_LOGINFILTER_H
#define DROGON_HTTP_LOGINFILTER_H

#pragma once
#include "utils/checkloginUtils.h"
#include <drogon/HttpFilter.h>
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

using namespace drogon;
using namespace rapidjson;

namespace drogon {
class DROGON_EXPORT LoginFilter final : public HttpFilter<LoginFilter>
{
  public:
    LoginFilter() = default;

    void doFilter(const HttpRequestPtr& req,
                  FilterCallback&& fcb,
                  FilterChainCallback&& fccb) override;
};
}  // namespace drogon

[[gnu::always_inline]] inline void LoginFilter::doFilter(const HttpRequestPtr& req, FilterCallback&& fcb, FilterChainCallback&& fccb)
{
    //Edit your logic here
    if (checkloginUtils::checklogin(req).has_value())
    {
        //Passed
        fccb();
        return;
    }

    // 创建一个 StringBuffer 和 PrettyWriter
    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer);

    // 开始对象
    writer.StartObject();

    // 添加其他键值对
    writer.Key("code");
    writer.Int(401);
    writer.Key("msg");
    writer.String("NoLogin");

    // 结束对象
    writer.EndObject();


    //Check failed
    /*const auto res = drogon::HttpResponse::newHttpJsonResponse(buffer.GetString());
    res->setStatusCode(k401Unauthorized);*/
    auto const resp = HttpResponse::newHttpResponse();
    resp->setContentTypeCodeAndCustomString(CT_APPLICATION_JSON, "utf-8");
    resp->setBody(buffer.GetString());
    resp->setStatusCode(k401Unauthorized);
    fcb(resp);
}

#endif  // DROGON_HTTP_LOGINFILTER_H
