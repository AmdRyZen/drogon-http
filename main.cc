#include "aop/Application.h"
#include <drogon/drogon.h>

int main()
{
    try
    {
        App::Application();

        // 注册 GzipFilter 插件
        drogon::app().enableGzip(true);

        drogon::app().loadConfigFile("config.json").run();

    } catch (const std::exception& e)
    {
        std::cout << "Application: err  " << e.what() << std::endl;
    }
    return 0;
}
