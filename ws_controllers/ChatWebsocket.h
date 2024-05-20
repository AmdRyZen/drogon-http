#pragma once
#include <drogon/PubSubService.h>
#include <drogon/WebSocketController.h>

using namespace drogon;
class ChatWebsocket final : public WebSocketController<ChatWebsocket>
{
public:
    void handleNewMessage(const WebSocketConnectionPtr&,
                          std::string&&,
                          const WebSocketMessageType&) override;
    void handleNewConnection(const HttpRequestPtr&,
                             const WebSocketConnectionPtr&) override;
    void handleConnectionClosed(const WebSocketConnectionPtr&) override;
    WS_PATH_LIST_BEGIN
    // list path definitions here;
    // WS_PATH_ADD("/path","filter1","filter2",...);
    WS_PATH_ADD("/chat");
    WS_PATH_LIST_END

private:
    PubSubService<std::string> chatRooms_;
};
