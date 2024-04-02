#include "aop/Application.h"
#include <drogon/drogon.h>

using namespace App;

int main()
{
    App::Application().initialization();


    // 注册 GzipFilter 插件
    drogon::app().enableGzip(true);

    drogon::app().loadConfigFile("config.json").run();

    return 0;
}
