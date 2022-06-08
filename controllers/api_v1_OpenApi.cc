#include "api_v1_OpenApi.h"
#include "service/SbcConvertService.h"
#include "utils/cipherUtils.h"
#include "utils/md5Utils.h"
#include "utils/redisUtils.h"
#include <drogon/HttpClient.h>

using namespace api::v1;
using namespace drogon;

// Add definition of your processing function here
void OpenApi::curlPost(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {

    std::string url = "http://127.0.0.1:9090";
    std::string param = "id=222230&accountName=xxxxx&vipLevel=6&money=10000&ip=127.0.0.1&gameId=0&orderId=11111111";
    std::string aes128Key = "xxxxxxxx";
    //std::string sign = "channelId=9900202007070002&timestamp=1638263374&key=Mm2xwNfsPpiFKExbGd3ledGZKmjJfScJ";

    auto client = drogon::HttpClient::newHttpClient(url);
    // aes
    std::string encryptedText = cipherUtils::encrypt_cbc(SbcConvertService::ws2s(SbcConvertService::s2ws(param)), aes128Key, aes128Key) + "==";
    std::cout << "encryptedText = " << encryptedText << std::endl;
    const std::string &pwd = cipherUtils::decrypt_cbc(encryptedText, aes128Key, aes128Key);
    std::cout << "pwd = " << pwd << std::endl;

    // md5
    unsigned char encrypt[] = "id=1111&timestamp=1638263374&key=xxxxx";
    unsigned char decrypt[16];
    MD5_CTX md5;
    md5Utils::MD5Init(&md5);
    md5Utils::MD5Update(&md5, encrypt, (int)strlen((char *)encrypt));
    md5Utils::MD5Final(&md5, decrypt);
    for (size_t i = 0; i < 16; i++){
        printf("%02x", decrypt[i]);
    }
    std::cout << std::endl;

    Json::Value params;
    params["channelId"] = "1111111111";
    params["timestamp"] = "1638263374";
    params["param"] = encryptedText;
    params["sign"] = "8482024d6c64fe364873725ea0e19008";

    std::cout << "__params = " <<  params.toStyledString() << std::endl;

    auto request = drogon::HttpRequest::newHttpRequest();
    request->addHeader("Content-Type", "application/json");
    request->setBody(params.toStyledString());
    request->setMethod(drogon::Post);
    request->setPath("/api/v1/curlPost");
    request->setPathEncode(true);
    client->sendRequest(
            request, [](ReqResult result, const HttpResponsePtr &response) {
                if (result != ReqResult::Ok)
                {
                    std::cout
                            << "error while sending request to server! result: "
                            << result << std::endl;
                    return;
                }

            if (200 != response->statusCode()) {
                std::cout << "cpp-demo : 接收反馈error = " << response->statusCode() << std::endl;
            }
            std::cout << "cpp-demo : 接收反馈result = " <<  response->getBody() << std::endl;
    });


    Json::Value data;
    data["msg"] = "ok";
    data["code"] = 200;
    callback(HttpResponse::newHttpJsonResponse(std::move(data)));
}

Task<> OpenApi::getValue(const HttpRequestPtr req,
                  std::function<void(const HttpResponsePtr &)> callback) {
  std::stringstream command;
  command << "get " << "aa";
  Json::Value redis_value = co_await redisUtils::getCoroRedisValue(command.str());

  Json::Value ret;
  ret["msg"] = "ok";
  ret["code"] = 200;
  ret["redis_value"] = redis_value;
  co_return callback(HttpResponse::newHttpJsonResponse(std::move(ret)));
}
