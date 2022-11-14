#include "aop/Application.h"
#include <drogon/drogon.h>

using namespace App;

int main()
{
    App::Application().initialization();

    drogon::app().loadConfigFile("config.json").run();

    return 0;
}
