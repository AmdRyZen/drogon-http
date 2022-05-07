#pragma once
#include <drogon/HttpController.h>
#include "service/TrieService.h"

extern TrieService trieService;
using namespace drogon;
namespace api
{
    namespace v1
    {
        class User : public drogon::HttpController<User>
        {
        public:
            METHOD_LIST_BEGIN
                METHOD_ADD(User::login, "/login?userId={1}&passwd={2}", Post);
                METHOD_ADD(User::getInfo, "/{1}/getInfo?token={2}", Get);
                METHOD_ADD(User::getBanWord, "/getBanWord?word={1}", Get);
                METHOD_ADD(User::serdeJson, "/serdeJson", Get);
            //use METHOD_ADD to add your custom processing function here;
            //METHOD_ADD(User::get,"/{2}/{1}",Get);//path is /api/v1/User/{arg2}/{arg1}
            //METHOD_ADD(User::your_method_name,"/{1}/{2}/list",Get);//path is /api/v1/User/{arg1}/{arg2}/list
            //ADD_METHOD_TO(User::your_method_name,"/absolute/path/{1}/{2}/list",Get);//path is /absolute/path/{arg1}/{arg2}/list
            METHOD_LIST_END

            void login(const HttpRequestPtr &req,
                       std::function<void (const HttpResponsePtr &)> &&callback,
                       std::string &&userId,
                       const std::string &password
           );

            Task<> getInfo(const HttpRequestPtr req,
                         std::function<void (const HttpResponsePtr &)> callback,
                         std::string userId,
                         const std::string token
            );

            void getBanWord(const HttpRequestPtr &req,
                       std::function<void (const HttpResponsePtr &)> &&callback,
                       const std::string &word
            );

            void serdeJson(const HttpRequestPtr &req,
                        std::function<void (const HttpResponsePtr &)> &&callback
            );
            // your declaration of processing function maybe like this:
            // void get(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback,int p1,std::string p2);
            // void your_method_name(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback,double p1,int p2) const;
        };
    }
}
