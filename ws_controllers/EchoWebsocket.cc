#include "EchoWebsocket.h"
#include "utils/redisUtils.h"
#include "boost/format.hpp"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

using namespace rapidjson;

struct Subscriber
{
    std::string chatRoomName_;
    SubscriberID id_{};
};

void EchoWebsocket::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string&& message, const WebSocketMessageType& type)
{
    //write your application logic here
    try
    {
        // write your application logic here
        if (type == WebSocketMessageType::Ping || type == WebSocketMessageType::Pong)
        {
            LOG_DEBUG << "recv a ping";
            return;
        }

        if (!message.empty())
        {
            /*bool res;
            JSONCPP_STRING errs;
            Json::Value root, lang, mail;
            Json::CharReaderBuilder readerBuilder;

            std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
            res = jsonReader->parse(message.c_str(), message.c_str() + message.length(), &root, &errs);
            if (!res || !errs.empty())
            {
                return;
            }*/

            // 创建 RapidJSON 文档对象
            Document document;
            if (document.Parse(message.c_str()).HasParseError()) {
                return;
            }

            // 判断 JSON 是否为空
            if (document.IsNull()) {
                std::cerr << "JSON is empty!" << std::endl;
                return;
            }

            std::string command;
            // 解析并输出 JSON 数据
            if (document.HasMember("key") && document["key"].IsString()) {
                command = std::format("get {}", document["key"].GetString());
            }

            if (!wsConnPtr->disconnected())
            {
                // 获取Subscriber引用
                const auto& subscriber = wsConnPtr->getContextRef<Subscriber>();
                // 使用结构化绑定提取成员变量
                const auto& [chatRoomName, id] = subscriber;

                async_run([command, chatRoomName, this]() -> drogon::Task<>
                {
                    try
                    {
                        std::string data;
                        if (!command.empty())
                        {
                            data = co_await redisUtils::getCoroRedisValue(command);
                        }
                        chatRooms_.publish(chatRoomName, std::format("data = {}", data) );
                    }
                    catch (const std::exception& e)
                    {
                        std::cerr << "Error in async task: " << e.what() << std::endl;
                    }
                    co_return;
                });
            }
            command.clear();
        }
        else
        {
            //std::cout << "message = empty" << std::endl;
        }
    }
    catch (...)
    {
        std::cout << "handleNewMessage ..." << std::endl;
    }
}
void EchoWebsocket::handleNewConnection(const HttpRequestPtr& req, const WebSocketConnectionPtr& wsConnPtr)
{
    //write your application logic here
    std::cout << "handleNewConnection" << std::endl;

    Subscriber s;
    s.chatRoomName_ = req->getParameter("room_name");
    wsConnPtr->send(s.chatRoomName_);
    s.id_ = chatRooms_.subscribe(s.chatRoomName_,
                                 [wsConnPtr](const std::string& topic,
                                             const std::string& message) {
                                     // Supress unused variable warning
                                     (void)topic;
                                     wsConnPtr->send(message);
                                 });
    std::cout << "id = " << s.id_ << std::endl;
    std::cout << "chatRoomName = " << s.chatRoomName_ << std::endl;
    wsConnPtr->setContext(std::make_shared<Subscriber>(std::move(s)));
}
void EchoWebsocket::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{
    //write your application logic here
    try
    {
        //std::cout << "handleConnectionClosed" << std::endl;
        // 获取Subscriber引用
        const auto& subscriber = wsConnPtr->getContextRef<Subscriber>();
        // 使用结构化绑定提取成员变量
        const auto& [chatRoomName, id] = subscriber;

        chatRooms_.unsubscribe(chatRoomName, id);
    }
    catch (...)
    {
        std::cout << "handleConnectionClosed ..." << std::endl;
    }
}
