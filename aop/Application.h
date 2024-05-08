//
// Created by 神圣·凯莎 on 2022/5/12.
//

#ifndef LEARNING_CPP_APPLICATION_H
#define LEARNING_CPP_APPLICATION_H

#include "service/TrieService.h"
#include "threadPool/threadPool.h"
#include <drogon/drogon.h>
#include <filesystem>
#include <iostream>
#include <drogon/version.h>
#include <trantor/utils/Utilities.h>

inline TrieService trieService;

inline ThreadPool pool(4);

namespace App {
constexpr char drogon[] = "\n"
                      "                       .::::.\n"
                      "                     .::::::::.\n"
                      "                    :::::::::::  HELLO DROGON\n"
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

class Application final
{
  public:
    [[gnu::always_inline]] inline Application();

    ~Application() = default;

    Application initialization();
};

Application::Application()
{
    drogon::app().registerBeginningAdvice([]() {
        const auto tlsBackend = trantor::utils::tlsBackend();
        std::cout << drogon << std::endl;
        std::cout << "A utility for drogon" << std::endl;
        std::cout << "Version: " << DROGON_VERSION << std::endl;
        std::cout << "Git commit: " << DROGON_VERSION_SHA1 << std::endl;
        std::cout << "ssl/tls backend: " << tlsBackend << std::endl;

        std::string word_path;
        std::string stopped_path;
        word_path.append(std::filesystem::current_path()).append("/public/word.txt");
        stopped_path.append(std::filesystem::current_path()).append("/public/stopped.txt");
        TrieService::loadFromFile(word_path);
        TrieService::loadStopWordFromFile(stopped_path);
        std::cout << "trieService load is success!" << std::endl;
        std::cout << std::endl << std::endl;
    });

    drogon::app().registerPreRoutingAdvice([](const drogon::HttpRequestPtr& req,
                                              drogon::AdviceCallback&& acb,
                                              drogon::AdviceChainCallback&& accb) {
        // todo ...
        //std::cout << "preRouting1!" << std::endl;
        accb();
    });
}
}  // namespace App


#endif  //LEARNING_CPP_APPLICATION_H
