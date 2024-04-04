#include "api_v1_User.h"
#include "jwt-cpp/base.h"
#include "jwt-cpp/jwt.h"
#include "utils/redisUtils.h"
#include "filters/SqlFilter.h"
#include <filesystem>
#include <fstream>
#include <drogon/drogon.h>
#include "models/XxlJobInfo.h"
#include <drogon/orm/Mapper.h>

using namespace api::v1;
using namespace drogon_model::xxl_job;
using namespace drogon::orm;
using namespace drogon;

//add definition of your processing function here
void User::login(const HttpRequestPtr& req,
                 std::function<void(const HttpResponsePtr&)>&& callback,
                 std::string&& userId,
                 const std::string& password)
{
    Json::Value data;
    try
    {
        if (req->getJsonObject() == nullptr || req->getJsonObject()->empty())
        {
            data["msg"] = "json is empty";
            return callback(HttpResponse::newHttpJsonResponse(data));
        }

        LOG_INFO << "userId= " << userId << " login";
        auto json = req->getJsonObject();
        LOG_INFO << "auto json = req.getJsonObject();= " << (*json)["name"].asString() << " ";
        // ...

        auto token = jwt::create()
                         .set_issuer("auth0")
                         .set_type("JWS")
                         .set_payload_claim("user_id", jwt::claim(std::string("123456")))
                         .set_payload_claim("name", jwt::claim(std::string("xxxxx")))
                         .set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds{drogon::app().getCustomConfig()["jwt-sessionTime"].asInt()})
                         .sign(jwt::algorithm::hs256{drogon::app().getCustomConfig()["jwt-secret"].asString()});

        std::cout << "secret = " << drogon::app().getCustomConfig()["jwt-secret"].asString() << std::endl;
        std::cout << "sessionTime = " << drogon::app().getCustomConfig()["jwt-sessionTime"].asInt() << std::endl;

        data["msg"] = "ok";
        data["name"] = (*json)["name"].asString();
        data["token"] = token;
        data["user_id"] = userId;
        return callback(HttpResponse::newHttpJsonResponse(data));
    }
    catch (...)
    {
        data["msg"] = "loginError";
        return callback(HttpResponse::newHttpJsonResponse(std::move(data)));
    }
}

template <typename... Arguments>
drogon::Task<drogon::orm::Result> dynamicQuery(std::string dynamicSql, Arguments &&...args)
{
    auto clientPtr = drogon::app().getFastDbClient();
    auto result = co_await clientPtr->execSqlCoro(dynamicSql + " order by id asc limit 10 ", args...);
    co_return result;
}

Task<> User::getInfo(const HttpRequestPtr req,
                     std::function<void(const HttpResponsePtr&)> callback,
                     std::string userId,
                     const std::string token)
{
    LOG_INFO << "User " << userId << " get his information";

    auto clientPtr = drogon::app().getFastDbClient();

    Json::Value item;
    Json::Value data;
    std::int32_t num_users = 0;
    std::string redis_value;

    try
    {
        // 基本 SQL 查询语句
        std::string baseSql = "SELECT * FROM xxl_job_info WHERE 1=1";
        std::string baseCountSql = "SELECT count(1) FROM xxl_job_info WHERE 1=1";

        // 条件参数
        std::vector<Condition<std::string>> conditions;
        conditions.push_back({"author", "!=", "xxx"});
        conditions.push_back({"id", "<", "3"});

        DynamicResult resultBase = buildDynamicQuery(baseSql, conditions);
        DynamicResult resultBaseCount = buildDynamicQuery(baseCountSql, conditions);
        // 构建动态 SQL 查询语句
        std::string dynamicSql = resultBase.baseSql.str();
        std::string dynamicCountSql = resultBaseCount.baseSql.str();

        std::cout << "dynamicSql: " << dynamicSql << std::endl;
        std::cout << "dynamicCountSql: " << dynamicCountSql << std::endl;
        for (const auto& param : resultBase.parameters)
            std::cout << "resultBase params: " << param.c_str() << std::endl;

        for (const auto& param : resultBaseCount.parameters)
            std::cout << "resultBaseCount params: " << param.c_str() << std::endl;



        //co_await clientPtr->execSqlCoro("update f_user set username = ? where id = ? limit 1", "xxxix", 2);
        auto transPtr = co_await clientPtr->newTransactionCoro();
        try
        {
            co_await transPtr->execSqlCoro("update xxl_job_info set author = ? where id = ? limit 1", "aa", 1);
            co_await transPtr->execSqlCoro("update xxl_job_info set author = ? where id = ? limit 1", "bb", 2);
            //throw std::runtime_error("hahaha");
        }
        catch (const drogon::orm::DrogonDbException& e)
        {
            transPtr->rollback();
            std::cout << "update failed: " << e.base().what() << std::endl;
            LOG_ERROR << "update failed: " << e.base().what();
        }

        std::vector<drogon::orm::Field> params;
        //params.emplace_back("Alice"); // 字符串参数

        *clientPtr  << "select * from xxl_job_info where author != ? and id = ?"
            << "xxx" << 1
            >> [](const drogon::orm::Result &result)
            {
                std::cout << result.size() << " rows selected!" << std::endl;
                int i = 0;
                for (const auto& row : result)
                {
                    std::cout << i++ << ": author is " << row["author"].as<std::string>() << std::endl;
                }
            }
        >> [](const orm::DrogonDbException &e)
        {
            std::cerr << "error1:" << e.base().what() << std::endl;
        };


        *clientPtr << "select "
                     "    a.id, "
                     "    a.author "
                     "from "
                     "    xxl_job_info a "
                     "inner join xxl_job_info u on "
                     "    a.id = u.id "
                     "where u.author = ?"
                  << "xxx"
                >> [](const drogon::orm::Result &result)
        {
            std::cout << result.size() << " rows selected!" << std::endl;
            int i = 0;
            for (const auto& row : result)
            {
                std::cout << i++ << ": author is " << row["author"].as<std::string>() << std::endl;
            }
        }
            >> [](const orm::DrogonDbException &e)
        {
            std::cerr << "error2:" << e.base().what() << std::endl;
        };

        auto result = co_await clientPtr->execSqlCoro(dynamicSql);
        auto count = co_await clientPtr->execSqlCoro(dynamicCountSql);

        std::for_each(result.begin(), result.end(), [&item, &data](const auto& row) {
            item["id"] = row["id"].template as<std::int64_t>();
            item["author"] = row["author"].template as<std::string>();
            item["job_desc"] = row["job_desc"].template as<std::string>();
            data.append(item);
            item.clear();
        });
        num_users = count[0][0].as<std::int32_t>();

        auto aa = Criteria(XxlJobInfo::Cols::_id, CompareOperator::LE, 1);
        std::cout << "XxlJobInfo: " << aa.criteriaString() << std::endl;

        // 构建查询条件
        auto criteria = Criteria(XxlJobInfo::Cols::_id, CompareOperator::EQ, 1) && Criteria(XxlJobInfo::Cols::_author, CompareOperator::EQ, "aa");
        std::cout << "criteria sql : " << "SELECT * FROM xxl_job_info WHERE " + criteria.criteriaString() << std::endl;

        // 创建SqlBinder对象
        std::string sql = "SELECT * FROM xxl_job_info WHERE id = ? and author = ?";
        auto nn = *clientPtr << sql;
        std::vector<std::string> values = {"1", "aa"};
        for (const auto &value : values)
        {
            nn << value;
        }
        nn >> [](const Result &r) {
            std::cout << "r.affectedRows() : " << r.affectedRows() << std::endl;
        };


        std::string sql1 = "SELECT * FROM xxl_job_info WHERE id = 1 and author = 'aa'";
        auto zz = clientPtr->execSqlCoro(sql1);
        for (const auto &value : values)
        {
            //co_await (*zz) << value;
        }

        auto r = co_await zz;
        std::cout << "Affected rows: " << r.affectedRows() << std::endl;
       /* Mapper<XxlJobInfo> mp(clientPtr);
        mp.findBy(criteria);*/

        // 执行查询
        /*auto xxx = co_await clientPtr->execSqlCoro("SELECT * FROM xxl_job_info WHERE " + criteria.criteriaString());
        std::cout << "xxx: " << xxx.size() << std::endl;*/
    }
    catch (const std::exception& e)
    {
        std::cerr << "error3:" << e.what() << std::endl;
    }

    std::stringstream command;
    command << "get " << "aa";

    redis_value = co_await redisUtils::getCoroRedisValue(command.str());


    //验证token有效性等
    //读数据库或缓存获取用户信息
    Json::Value ret;
    ret["msg"] = "ok";
    ret["code"] = 200;
    ret["redis_value"] = redis_value;
    ret["num_users"] = num_users;
    ret["data"] = std::move(data);
    co_return callback(HttpResponse::newHttpJsonResponse(std::move(ret)));
}

void User::getBanWord(const HttpRequestPtr& req,
                      std::function<void(const HttpResponsePtr&)>&& callback,
                      const std::string& word)
{
    std::vector<std::string> words = {
        // 字母
        "FUCK",      // 全大写
        "FuCk",      // 混合
        "F&uc&k",    // 特殊符号
        "F&uc&&&k",  // 连续特殊符号
        "ＦＵｃｋ",  // 全角大小写混合
        "F。uc——k",  // 全角特殊符号
        "fＵｃk",    // 全角半角混合
        "fＵ😊ｃk",  // Emotion表情，测试

        // 简体中文
        "微信",
        "微——信",              // 全角符号
        "微【】、。？《》信",  // 全角重复词
        "微。信",
        "VX",
        "vx",                                   // 小写
        "V&X",                                  // 特殊字符
        "微!., #$%&*()|?/@\"';[]{}+~-_=^<>信",  // 30个特殊字符 递归
        "扣扣",
        "扣_扣",
        "QQ",
        "Qq",
    };

    std::for_each(words.begin(), words.end(), [&](const auto& item) {
        auto t1 = std::chrono::steady_clock::now();

        std::wstring result = trieService.replaceSensitive(SbcConvertService::s2ws(item));

        auto t2 = std::chrono::steady_clock::now();
        double dr_ms = std::chrono::duration<double, std::milli>(t2 - t1).count();
        std::cout << "[cost: " << dr_ms << " ms]" << item << " => " << SbcConvertService::ws2s(result) << std::endl;
    });

    Json::Value data;
    data["msg"] = "ok";
    data["code"] = 200;
    data["banWord"] = SbcConvertService::ws2s(trieService.replaceSensitive(SbcConvertService::s2ws(word)));
    callback(HttpResponse::newHttpJsonResponse(std::move(data)));
}

void User::serdeJson(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    std::string word_path;
    word_path.append(std::filesystem::current_path()).append("/public/world-cities.geojson");
    std::ifstream ifs(word_path, std::ios_base::in);
    std::string str;
    getline(ifs, str);
    //std::cout << " serdeJson = " << str << std::endl;

    auto t1 = std::chrono::steady_clock::now();

    bool res;
    JSONCPP_STRING errs;
    Json::Value root, list;
    Json::CharReaderBuilder readerBuilder;

    std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
    res = jsonReader->parse(str.c_str(), str.c_str() + str.length(), &root, &errs);
    if (!res || !errs.empty())
    {
        std::cout << "parseJson err. " << errs << std::endl;
        return;
    }

    auto t2 = std::chrono::steady_clock::now();
    double dr_ms = std::chrono::duration<double, std::milli>(t2 - t1).count();
    std::cout << "[cost: " << dr_ms << " ms]" << std::endl;
    std::cout << "type: " << root["type"].asString() << std::endl;

    /* list = root["features"];
    for (int i = 0; i < list.size(); ++i) {
        std::cout << list[i] << " ";
    }*/

    Json::Value data;
    data["msg"] = "ok";
    data["code"] = 200;
    callback(HttpResponse::newHttpJsonResponse(std::move(data)));
}

void User::quit(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    drogon::app().quit();
    auto data = HttpResponse::newHttpResponse();
    data->setStatusCode(HttpStatusCode::k204NoContent);
    callback(data);
}
