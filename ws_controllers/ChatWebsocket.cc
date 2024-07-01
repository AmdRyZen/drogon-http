#include "ChatWebsocket.h"
#include "utils/redisUtils.h"
#include "boost/format.hpp"
#include "rapidjson/document.h"
#include "user.pb.h"

using namespace rapidjson;

struct Subscriber
{
    std::string chatRoomName_;
    SubscriberID id_{};
};

void ChatWebsocket::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string&& message, const WebSocketMessageType& type)
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

            std::string action;
            if (document.HasMember("action") && document["action"].IsString())
            {
                action = document["action"].GetString();
            }
            std::string msgContent = document["msgContent"].GetString();

            // 在处理用户退出时检查连接状态
            if (!wsConnPtr->disconnected())
            {
                const auto& subscriber = wsConnPtr->getContextRef<Subscriber>();
                const auto& [chatRoomName, id] = subscriber;

                //auto sharedThis = shared_from_this();
                async_run([action, msgContent, command, chatRoomName, id, this]() -> Task<>
                {
                    try
                    {
                        std::string data;
                        if (!command.empty())
                        {
                            data = co_await redisUtils::getCoroRedisValue(command);
                        }

                        if (!action.empty())
                        {
                            if (action == "message")
                            {
                                // 发送消息到聊天室
                                const std::string formattedMessage = std::format(R"({{"sender": "{}", "message": "{} ====> {}}})", id, msgContent, data);
                                // protobuf
                                std::string buffer{};
                                dto::UserData userData;
                                userData.set_id(std::to_string(id));
                                userData.set_name(action);
                                userData.set_message(msgContent);
                                userData.SerializeToString(&buffer);
                                // 清理 Protobuf 库
                                google::protobuf::ShutdownProtobufLibrary();
                                chatRooms_.publish(chatRoomName, buffer);
                            }
                            // 其他操作...
                        }
                    }
                    catch (const std::exception& e)
                    {
                        std::cerr << "Error in async task: " << e.what() << std::endl;
                    }
                    co_return;
                });
            }
        }
    }
    catch (...)
    {
        std::cout << "handleNewMessage ..." << std::endl;
    }
}
void ChatWebsocket::handleNewConnection(const HttpRequestPtr& req, const WebSocketConnectionPtr& wsConnPtr)
{
    //write your application logic here
    std::cout << "handleNewConnection" << std::endl;

    Subscriber s;
    s.chatRoomName_ = req->getHeader("room_name");
    if (s.chatRoomName_.empty()) {
        s.chatRoomName_ = "default_room"; // 设置默认的聊天室名称
    }
    std::string userName_ = req->getHeader("name");
    if (userName_.empty()) {
        userName_ = "default_name"; // 设置默认的名称
    }
    // 处理用户加入聊天室
    wsConnPtr->send(std::format("欢迎 {} 加入我们 {}", userName_, s.chatRoomName_));
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
void ChatWebsocket::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
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
        // todo 暂时不确定是否需要
        if (chatRooms_.size() == 0)
        {
            std::cout << "chatRooms_.size() = " << chatRooms_.size() << std::endl;
            chatRooms_.clear();
        }
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
