#include "api_v1_OpenApi.h"
#include "nlohmann/json.hpp"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "service/SbcConvertService.h"
#include "threadPool/threadPool.h"
#include "utils/cipherUtils.h"
#include "utils/md5Utils.h"
#include "utils/redisUtils.h"
#include <drogon/HttpClient.h>
#include <taskflow/taskflow.hpp>  // Taskflow is header-only
#include "boost/version.hpp"
#include "boost/regex.hpp"
#include "utils/printer.h"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/format.hpp>

using namespace api::v1;
using namespace drogon;
using json = nlohmann::json;
using namespace boost::gregorian;

void printerFunc()
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    // 创建io_service对象
    io_service io;
    // 创建printer对象，初始化定时器并启动异步等待操作
    printer p(io, 5);
    // 运行io_service对象，处理所有事件（包括回调函数）
    io.run();
}

Task<> OpenApi::boost(const HttpRequestPtr req, std::function<void(const HttpResponsePtr&)> callback)
{
    std::cout << BOOST_LIB_VERSION << std::endl;
    std::cout << BOOST_VERSION << std::endl;

    // std::async函数启动一个异步任务，传入func1和一个int值作为参数
    std::future<void> f = std::async(printerFunc);
    // 在主线程中做一些其他事情
    std::cout << "Doing something else in main thread." << std::endl;

    std::cout << boost::format("Hello %s! You are %d years old.") % "Tom" % 25 << std::endl;

    std::string email = "someone@example.com";
    boost::regex pattern(R"(\b[a-zA-Z0-9._%-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4}\b)");
    if (boost::regex_match(email, pattern))
        std::cout << "Valid email address." << std::endl;
    else
        std::cout << "Invalid email address." << std::endl;

    boost::random::mt19937 rng;                            // create a random number generator
    boost::random::uniform_int_distribution<> dist(0, 9);  // create a uniform distribution
    for (int i = 0; i < 10; ++i)                           // generate and print 10 random numbers
        std::cout << dist(rng) << " ";
    std::cout << std::endl;

    // 创建一个date对象，表示今天的日期
    date today = day_clock::local_day();
    std::cout << "Today is: " << today << std::endl;

    // 创建一个date对象，表示2023年2月14日
    date valentine(2023, Feb, 14);
    std::cout << "Valentine's day is: " << valentine << std::endl;

    // 创建一个date对象，表示从字符串解析的日期
    date birthday(from_string("2000-01-01"));
    std::cout << "Birthday is: " << birthday << std::endl;

    // 计算两个日期之间的差值，返回一个date_duration对象
    date_duration days_to_valentine = valentine - today;
    std::cout << "Days to Valentine's day: " << days_to_valentine.days() << std::endl;

    Json::Value ret;
    ret["msg"] = "ok";
    ret["code"] = 200;
    co_return callback(HttpResponse::newHttpJsonResponse(std::move(ret)));
}

// Add definition of your processing function here
void OpenApi::curlPost(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    std::string url = "http://127.0.0.1:9090";
    std::string param = "id=222230&bb=xxxxx&cc=6&dd=10000&ip=127.0.0.1&zz=0&ff=11111111";
    std::string aes128Key = "xxxxxxxx";

    auto client = drogon::HttpClient::newHttpClient(url);
    // aes
    std::string encryptedText = cipherUtils::encrypt_cbc(SbcConvertService::ws2s(SbcConvertService::s2ws(param)), aes128Key, aes128Key);
    std::cout << "encryptedText = " << encryptedText << std::endl;
    const std::string& pwd = cipherUtils::decrypt_cbc(encryptedText, aes128Key, aes128Key);
    std::cout << "pwd = " << pwd << std::endl;

    // md5
    unsigned char encrypt[] = "id=1111&timestamp=1638263374&key=xxxxx";
    unsigned char decrypt[16];
    MD5_CTX md5;
    md5Utils::MD5Init(&md5);
    md5Utils::MD5Update(&md5, encrypt, (int)strlen((char*)encrypt));
    md5Utils::MD5Final(&md5, decrypt);
    for (unsigned char i : decrypt)
    {
        printf("%02x", i);
    }
    std::cout << std::endl;

    Json::Value params;
    params["channelId"] = "1111111111";
    params["timestamp"] = "1638263374";
    params["param"] = encryptedText;
    params["sign"] = "8482024d6c64fe364873725ea0e19008";

    std::cout << "__params = " << params.toStyledString() << std::endl;

    auto request = drogon::HttpRequest::newHttpRequest();
    request->addHeader("Content-Type", "application/json");
    request->setBody(params.toStyledString());
    request->setMethod(drogon::Post);
    request->setPath("/api/v1/curlPost");
    request->setPathEncode(true);
    client->sendRequest(
        request,
        [](ReqResult result, const HttpResponsePtr& response) {
            if (result != ReqResult::Ok)
            {
                std::cout
                    << "error while sending request to server! result: "
                    << result << std::endl;
                return;
            }

            if (200 != response->statusCode())
            {
                std::cout << "cpp-demo : 接收反馈error = " << response->statusCode() << std::endl;
            }
            std::cout << "cpp-demo : 接收反馈result = " << response->getBody() << std::endl;
        });

    Json::Value data;
    data["msg"] = "ok";
    data["code"] = 200;
    callback(HttpResponse::newHttpJsonResponse(std::move(data)));
}

Task<> OpenApi::getValue(const HttpRequestPtr req,
                         std::function<void(const HttpResponsePtr&)> callback)
{
    std::stringstream command;
    command << "get "
            << "aa";
    Json::Value redis_value = co_await redisUtils::getCoroRedisValue(command.str());

    Json::Value ret;
    ret["msg"] = "ok";
    ret["code"] = 200;
    ret["redis_value"] = redis_value;
    co_return callback(HttpResponse::newHttpJsonResponse(std::move(ret)));
}

Task<> OpenApi::fastJson(const HttpRequestPtr req, std::function<void(const HttpResponsePtr&)> callback)
{
    //GOOGLE_PROTOBUF_VERIFY_VERSION;
    // protobuf
    /*dto::UserData userData;
    userData.set_id(1);
    userData.set_name("name");

    std::string buff{};
    auto t1 = std::chrono::steady_clock::now();
    userData.SerializeToString(&buff);
    auto t2 = std::chrono::steady_clock::now();
    //纳秒级
    double dr_ns = std::chrono::duration<double, std::nano>(t2 - t1).count();
    //微妙级
    double dr_us = std::chrono::duration<double, std::micro>(t2 - t1).count();
    std::cout << "[pb cost: " << dr_ns << " ns]" << std::endl;
    std::cout << "[pb cost: " << dr_us << " us]" << std::endl;

    //------------------解析----------------------
    dto::UserData rsp2{};
    if (!rsp2.ParseFromString(buff))
    {
        std::cout << "parse error\n";
    }
    auto name = rsp2.name();
    std::cout << "name:" << name << std::endl;*/

    // jsoncpp
    Json::Value root;
    root["id"] = 1;
    root["name"] = "b";
    auto t3 = std::chrono::steady_clock::now();
    auto cppjson_content = root.toStyledString();
    auto t4 = std::chrono::steady_clock::now();
    //纳秒级
    double dr_ns1 = std::chrono::duration<double, std::nano>(t4 - t3).count();
    std::cout << "[jsoncpp cost: " << dr_ns1 << " ns]" << std::endl;

    // rapidjson
    rapidjson::StringBuffer buf;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buf);  // it can word wrap
    writer.StartObject();
    writer.Key("id");
    writer.Int(1);
    writer.Key("name");
    writer.String("a");
    writer.EndObject();
    auto t5 = std::chrono::steady_clock::now();
    for (auto i = 0; i < 1000; i++)
    {
        buf.GetString();
    }
    auto t6 = std::chrono::steady_clock::now();
    //纳秒级
    double dr_ns2 = std::chrono::duration<double, std::nano>(t6 - t5).count();
    std::cout << "[rapidjson cost: " << dr_ns2 << " ns]" << std::endl;

    // onlohmannJson
    json onlohmannJson;
    onlohmannJson["id"] = 1;
    onlohmannJson["name"] = "c";
    auto t7 = std::chrono::steady_clock::now();
    for (auto i = 0; i < 1000; i++)
    {
        onlohmannJson.dump();
    }
    auto t8 = std::chrono::steady_clock::now();
    //纳秒级
    double dr_ns3 = std::chrono::duration<double, std::nano>(t8 - t7).count();
    std::cout << "[onlohmannJson cost: " << dr_ns3 << " ns]" << std::endl;

    std::cout << "---------------xx-----------------" << std::endl;

    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(drogon::CT_APPLICATION_JSON);
    resp->setBody(onlohmannJson.dump());
    co_return callback(resp);
}

std::atomic<int64_t> value(0);
inline void threadF()
{
    for (int i = 0; i < 100; ++i)
    {
        value++;
    }
}

int64_t value1 = 0;
std::mutex mtx;
inline void threadF1()
{
    for (int i = 0; i < 100; ++i)
    {
        std::lock_guard<std::mutex> lk(mtx);
        thread_local int count = 0;
        ++count;
        std::cout << "count: " << count << std::endl;
        // 当前线程休眠1毫秒
        //std::this_thread::sleep_for(std::chrono::milliseconds(1));
        value1++;
    }
}

Task<> OpenApi::threadPool(const HttpRequestPtr req, std::function<void(const HttpResponsePtr&)> callback)
{
    auto result = pool.enqueue([] {
        threadF();
        threadF1();
    });
    auto result1 = pool.enqueue([] {
        threadF();
        threadF1();
    });
    result.wait();
    result1.wait();
    std::cout << "value = " << value << std::endl;
    std::cout << "value1 = " << value1 << std::endl;

    // taskflow.github.io
    tf::Executor executor;
    tf::Taskflow taskflow;

    auto clientPtr = drogon::app().getFastDbClient();
    auto ret = co_await clientPtr->execSqlCoro("select count(1) from f_user where username != ?", "薯条三兄弟");
    auto count = ret[0][0].as<std::int32_t>();

    // now - use std::future instead
    std::future<bool> fu = executor.async([&count]() {
        std::cout << "async task returns boolean" << std::endl;
        std::cout << "count = " << count << std::endl;
        if (count >= 0)
        {
            return true;
        }
        return false;
    });
    fu.get();

    executor.silent_async([]() {
        std::cout << "async task of no return" << std::endl;
    });

    // launch an asynchronous task from a running task
    taskflow.emplace([&]() {
        executor.async([]() {
            std::cout << "async task within a task" << std::endl;
        });
    });

    executor.run(taskflow).wait();

    bool future_ret = false;
    if (fu.get())
    {
        future_ret = fu.get();
    }

    double foo = 0.0;
    double bar = 1.0;
    auto res = foo <=> bar;
    if (res < 0)
        std::cout << "foo 小于 bar" << std::endl;
    else if (res > 0)
        std::cout << "foo 大于 bar" << std::endl;
    else  // (res == 0)
        std::cout << "foo 与 bar 相等" << std::endl;

    co_return callback(HttpResponse::newHttpJsonResponse(future_ret));
}

Task<> OpenApi::fix(const HttpRequestPtr req, std::function<void(const HttpResponsePtr&)> callback)
{
    // mysqlbinlog --no-defaults --base64-output=decode-rows -v ./mysql-bin.000131 --result-file=./2.sql

    auto clientPtr = drogon::app().getFastDbClient();

    struct Data : public Json::Value
    {
        Json::Value data;
        Json::Value item;
        Data()
          : data()
        {}
    } _data;

    /*template<
        std::size_t Len,
        std::size_t Align = */
    /*default-alignment*/ /*
        >
    struct aligned_storage;
    (since C++11)(deprecated in C++23)*/

    //static std::aligned_storage<sizeof(Data), alignof(Data)>::type data;
    //Data* attr = new (&data) Data;
    //attr->data["data"] = "aligned_storage";
    //std::cout << attr->data << std::endl;
    //std::cout << "attr = " << sizeof(attr) << std::endl;
    std::cout << "__data = " << sizeof(_data) << std::endl;

    auto lhaving = co_await clientPtr->execSqlCoro("select user_id from xxxxx where  original_number != 0 and op_number != 0  group by user_id having count(1) > 1 order by create_time");
    for (std::size_t n = 0; n < lhaving.size(); ++n)
    {
        auto userId = lhaving[n]["user_id"].template as<std::int32_t>();

        // ....
        auto result = co_await clientPtr->execSqlCoro("select * from xxxxxxxx where original_number != 0 and op_number != 0 and user_id = ? order by create_time desc", userId);

        for (std::size_t i = 0; i < result.size(); ++i)
        {
            auto original_number = result[i]["original_number"].template as<std::int32_t>();
            auto op_number = result[i]["op_number"].template as<std::int32_t>();

            int32_t next_original_number = 0;
            if (i < result.size() - 1)
            {
                next_original_number = result[i + 1]["original_number"].template as<std::int32_t>();
            }

            if ((original_number + op_number) != next_original_number && next_original_number != 0)
            {
                _data.item["record_id"] = result[i]["record_id"].template as<std::int32_t>();
                _data.item["user_id"] = result[i]["user_id"].template as<std::int32_t>();
                _data.item["original_number"] = result[i]["original_number"].template as<std::int32_t>();
                _data.item["op_number"] = result[i]["op_number"].template as<std::int32_t>();
                _data.item["next_original_number"] = next_original_number;
                _data.item["diff"] = original_number + op_number - next_original_number;

                _data.data.append(_data.item);
                _data.item.clear();
            }
        }
    }

    std::cout << "size  = " << _data.data.size() << std::endl;

    Json::Value ret;
    ret["msg"] = "ok";
    ret["data"] = _data.data;

    co_return callback(HttpResponse::newHttpJsonResponse(std::move(ret)));
}

Task<> OpenApi::random(const HttpRequestPtr req, std::function<void(const HttpResponsePtr&)> callback)
{
    std::default_random_engine random(time(nullptr));

    std::uniform_int_distribution<int> int_dis(0, 100);        // 整数均匀分布
    std::uniform_real_distribution<float> real_dis(0.0, 1.0);  // 浮点数均匀分布

    std::vector<int32_t> value;
    for (int i = 0; i < 10; ++i)
    {
        auto inta = int_dis(random);
        value.push_back(inta);
        std::cout << inta << ' ';
    }
    std::cout << std::endl;

    for (int i = 0; i < 10; ++i)
    {
        std::cout << real_dis(random) << ' ';
    }
    std::cout << std::endl;

    auto result = std::minmax_element(value.begin(), value.end());
    std::cout << "min element at: " << *(result.first) << std::endl;
    std::cout << "max element at: " << *(result.second) << std::endl;
    std::sort(value.begin(), value.end());
    std::for_each(value.begin(), value.end(), [&](const auto& item) {
        std::cout << item << std::endl;
    });
    value.clear();

    Json::Value ret;
    ret["msg"] = "ok";
    co_return callback(HttpResponse::newHttpJsonResponse(std::move(ret)));
}