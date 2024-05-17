#include "EchoWebsocket.h"
#include "utils/redisUtils.h"
#include "boost/format.hpp"

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
        LOG_DEBUG << "new websocket message:" << message;

        if (type == WebSocketMessageType::Ping)
        {
            LOG_DEBUG << "recv a ping";
            return;
        }

        if (!message.empty())
        {
            bool res;
            JSONCPP_STRING errs;
            Json::Value root, lang, mail;
            Json::CharReaderBuilder readerBuilder;

            std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
            res = jsonReader->parse(message.c_str(), message.c_str() + message.length(), &root, &errs);
            if (!res || !errs.empty())
            {
                //std::cout << "parseJson err. " << errs << std::endl;
                return;
            }

            /*std::cout << "key: " << root["key"].asString() << std::endl;
            std::cout << "Name: " << root["Name"].asString() << std::endl;
            std::cout << "Age: " << root["Age"].asInt() << std::endl;
            lang = root["Language"];
            std::cout << "Language: ";
            for (int i = 0; i < lang.size(); ++i) {
                std::cout << lang[i] << " ";
            }
            std::cout << std::endl;
            mail = root["E-mail"];
            std::cout << "Netease: " << mail["Netease"].asString() << std::endl;
            std::cout << "Hotmail: " << mail["Hotmail"].asString() << std::endl;*/

            /*std::stringstream command;
            command << "get " << root["key"].asString().c_str();*/
            // 创建一个格式化字符串
            boost::format command("get %s");
            // 按顺序绑定参数
            command % root["key"].asString();

            if (!wsConnPtr->disconnected())
            {
                // 获取Subscriber引用
                const auto& subscriber = wsConnPtr->getContextRef<Subscriber>();
                // 使用结构化绑定提取成员变量
                const auto& [chatRoomName, id] = subscriber;

                async_run([commandStr = command.str(), chatRoomName, this]() -> drogon::Task<>
                {
                    try
                    {
                        //const std::string data = co_await redisUtils::getCoroRedisValue(commandStr);
                        chatRooms_.publish(chatRoomName, "data = ");
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
        auto& s = wsConnPtr->getContextRef<Subscriber>();
        chatRooms_.unsubscribe(s.chatRoomName_, s.id_);
    }
    catch (...)
    {
        std::cout << "handleConnectionClosed ..." << std::endl;
    }
}
