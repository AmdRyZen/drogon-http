#include <drogon/drogon.h>
#include <filesystem>
#include "config.h.in"
#include "service/TrieService.h"

TrieService trieService;

int main() {
    //Load config file
    //drogon::app().loadConfigFile("../config.json");
    //Run HTTP framework,the method will block in the internal event loop
    /*drogon::app().setLogPath("./")
            //.setLogLevel(trantor::Logger::kWarn)
            .addListener("0.0.0.0", 9090)
            .setThreadNum(16)
            .enableDateHeader(false)
            .enableServerHeader(false)
            //.enableRunAsDaemon()
            .run();*/
    std::string drogon = "\n"
                         "                       .::::.\n"
                         "                     .::::::::.\n"
                         "                    :::::::::::  FUCK YOU\n"
                         "                ..:::::::::::'\n"
                         "              '::::::::::::'\n"
                         "                .::::::::::\n"
                         "           '::::::::::::::..\n"
                         "                ..::::::::::::.\n"
                         "              ``::::::::::::::::\n"
                         "               ::::``:::::::::'        .:::.\n"
                         "              ::::'   ':::::'       .::::::::.\n"
                         "            .::::'      ::::     .:::::::'::::.\n"
                         "           .:::'       :::::  .:::::::::' ':::::.\n"
                         "          .::'        :::::.:::::::::'      ':::::.\n"
                         "         .::'         ::::::::::::::'         ``::::.\n"
                         "     ...:::           ::::::::::::'              ``::.\n"
                         "    ````':.          ':::::::::'                  ::::..\n"
                         "                       '.:::::'                    ':'````..\n"
                         "\n";
    /*std::string drogon = "    ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐\n"
                         "    │Esc│   │ F1│ F2│ F3│ F4│ │ F5│ F6│ F7│ F8│ │ F9│F10│F11│F12│ │P/S│S L│P/B│  ┌┐    ┌┐    ┌┐\n"
                         "    └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘  └┘    └┘    └┘\n"
                         "    ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐ ┌───┬───┬───┬───┐\n"
                         "    │~ `│! 1│@ 2│# 3│$ 4│% 5│^ 6│& 7│* 8│( 9│) 0│_ -│+ =│ BacSp │ │Ins│Hom│PUp│ │N L│ / │ * │ - │\n"
                         "    ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤ ├───┼───┼───┼───┤\n"
                         "    │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │{ [│} ]│ | \\ │ │Del│End│PDn│ │ 7 │ 8 │ 9 │   │\n"
                         "    ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘ ├───┼───┼───┤ + │\n"
                         "    │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │: ;│\" '│ Enter  │               │ 4 │ 5 │ 6 │   │\n"
                         "    ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐     ├───┼───┼───┼───┤\n"
                         "    │ Shift  │ Z │ X │ C │ V │ B │ N │ M │< ,│> .│? /│  Shift   │     │ ↑ │     │ 1 │ 2 │ 3 │   │\n"
                         "    ├─────┬──┴─┬─┴──┬┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐ ├───┴───┼───┤ E││\n"
                         "    │ Ctrl│    │Alt │         Space         │ Alt│    │    │Ctrl│ │ ← │ ↓ │ → │ │   0   │ . │←─┘│\n"
                         "    └─────┴────┴────┴───────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘ └───────┴───┴───┘";*/
    /*std::string drogon = "´´´´´´´´██´´´´´´´\n"
                         "´´´´´´´████´´´´´´\n"
                         "´´´´´████████´´´´\n"
                         "´´`´███▒▒▒▒███´´´´´\n"
                         "´´´███▒●▒▒●▒██´´´\n"
                         "´´´███▒▒▒▒▒▒██´´´´´\n"
                         "´´´███▒▒▒▒██´                      \n"
                         "´´██████▒▒███´´´´´                 \n"
                         "´██████▒▒▒▒███´´                  \n"
                         "██████▒▒▒▒▒▒███´´´´                \n"
                         "´´▓▓▓▓▓▓▓▓▓▓▓▓▓▒´´                 \n"
                         "´´▒▒▒▒▓▓▓▓▓▓▓▓▓▒´´´´´              \n"
                         "´.▒▒▒´´▓▓▓▓▓▓▓▓▒´´´´´              \n"
                         "´.▒▒´´´´▓▓▓▓▓▓▓▒                   \n"
                         "..▒▒.´´´´▓▓▓▓▓▓▓▒                  \n"
                         "´▒▒▒▒▒▒▒▒▒▒▒▒                      \n"
                         "´´´´´´´´´███████´´´´´              \n"
                         "´´´´´´´´████████´´´´´´´\n"
                         "´´´´´´´█████████´´´´´´\n"
                         "´´´´´´██████████´´´´             \n"
                         "´´´´´´██████████´´´                    \n"
                         "´´´´´´´█████████´´\n"
                         "´´´´´´´█████████´´´\n"
                         "´´´´´´´´████████´´´´´\n"
                         "________▒▒▒▒▒\n"
                         "_________▒▒▒▒\n"
                         "_________▒▒▒▒\n"
                         "________▒▒_▒▒\n"
                         "_______▒▒__▒▒\n"
                         "_____ ▒▒___▒▒\n"
                         "_____▒▒___▒▒\n"
                         "____▒▒____▒▒\n"
                         "___▒▒_____▒▒\n"
                         "███____ ▒▒\n"
                         "████____███\n"
                         "█ _███_ _█_███";*/
    std::cout << drogon << std::endl;

    std::cout << "current path:" << std::filesystem::current_path() << std::endl;

    std::string path;
    path.append(std::filesystem::current_path());

    std::string word_path;
    std::string stopped_path;
    word_path.append(std::filesystem::current_path()).append("/public/word.txt");
    stopped_path.append(std::filesystem::current_path()).append("/public/stopped.txt");
    trieService.loadFromFile(word_path);
    trieService.loadStopWordFromFile(stopped_path);

    drogon::app().registerPreRoutingAdvice([](const drogon::HttpRequestPtr &req,
                                      drogon::AdviceCallback &&acb,
                                      drogon::AdviceChainCallback &&accb) {
      LOG_DEBUG << "preRouting1";
      std::cout << "preRouting1!" << std::endl;
      accb();
    });

    drogon::app().registerBeginningAdvice(
        []() {
          LOG_DEBUG << "Event loop is running!";
          std::cout << "Event loop is running!" << std::endl;
        });

    drogon::app().loadConfigFile("config.json");
    drogon::app().run();
    return 0;
}
