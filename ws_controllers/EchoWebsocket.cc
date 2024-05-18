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
    try
    {
        if (type == WebSocketMessageType::Ping)
        {
            wsConnPtr->send("pong", WebSocketMessageType::Pong);
            LOG_DEBUG << "recv a ping";
            return;
        }

        if (!message.empty())
        {
            Document document;
            if (document.Parse(message.c_str()).HasParseError())
            {
                return;
            }

            if (document.IsNull())
            {
                std::cerr << "JSON is empty!" << std::endl;
                return;
            }

            std::string command;
            if (document.HasMember("key") && document["key"].IsString())
            {
                command = std::format("get {}", document["key"].GetString());
            }

            // 在处理用户退出时检查连接状态
            if (!wsConnPtr->disconnected())
            {
                const auto& subscriber = wsConnPtr->getContextRef<Subscriber>();
                const auto& [chatRoomName, id] = subscriber;

                auto sharedThis = shared_from_this();
                async_run([command, chatRoomName, sharedThis]() -> Task<>
                {
                    try
                    {
                        std::string_view data;
                        if (!command.empty())
                        {
                            data = co_await redisUtils::getCoroRedisValue(command);
                        }
                        sharedThis->chatRooms_.publish(chatRoomName, std::format("data = {}", data));
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
        // 退出所有房间
        chatRooms_.unsubscribe(chatRoomName, id);
        // 清理资源
        wsConnPtr->clearContext();

        std::cout << "handleConnectionClosed id = " << id << std::endl;
        std::cout << "handleConnectionClosed chatRoomName = " << chatRoomName << std::endl;
    }
    catch (...)
    {
        std::cout << "handleConnectionClosed ..." << std::endl;
    }
}
