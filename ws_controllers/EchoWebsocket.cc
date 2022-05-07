#include "EchoWebsocket.h"
#include "utils/redisUtils.h"
#include "drogon/Session.h"

struct Subscriber {
    std::string chatRoomName_;
    drogon::SubscriberID id_;
};

void EchoWebsocket::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    //write your application logic here
    try {
        if (!message.empty()) {
            bool res;
            JSONCPP_STRING errs;
            Json::Value root, lang, mail;
            Json::CharReaderBuilder readerBuilder;

            std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
            res = jsonReader->parse(message.c_str(), message.c_str() + message.length(), &root, &errs);
            if (!res || !errs.empty()) {
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

            std::stringstream command;
            command << "get " << root["key"].asString().c_str();

            if (!wsConnPtr->disconnected()) {
                drogon::async_run([wsConnPtr, &command, this]() -> drogon::Task<> {
                    std::string data = co_await redisUtils::getCoroRedisValue(command.str());
                    std::cout << "data: " << data << std::endl;
                    auto &s = wsConnPtr->getContextRef<Subscriber>();
                    chatRooms_.publish(s.chatRoomName_, std::to_string(s.id_));
                    co_return;
                });
            }
           /* std::optional<std::string> oi = redisUtils::getRedisValue(command.str());
            if (oi) {
                auto &s = wsConnPtr->getContextRef<Subscriber>();
                chatRooms_.publish(s.chatRoomName_, oi.value());
            }*/
        } else {
            //std::cout << "message = empty" << std::endl;
        }
    } catch(...) {
        std::cout << "handleNewMessage ..." << std::endl;
    }
}
void EchoWebsocket::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr& wsConnPtr)
{
    //write your application logic here
    std::cout << "handleNewConnection" << std::endl;

    Subscriber s;
    s.chatRoomName_ = req->getParameter("room_name");
    wsConnPtr->send(s.chatRoomName_);
    s.id_ = chatRooms_.subscribe(s.chatRoomName_,
                                 [wsConnPtr](const std::string &topic,
                                        const std::string &message) {
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
    try {
        std::cout << "handleConnectionClosed" << std::endl;
        auto &s = wsConnPtr->getContextRef<Subscriber>();
        chatRooms_.unsubscribe(s.chatRoomName_, s.id_);
    } catch(...) {
        std::cout << "handleConnectionClosed ..." << std::endl;
    }
}
