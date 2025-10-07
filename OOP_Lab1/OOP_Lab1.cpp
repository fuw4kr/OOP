#include "SocialNetwork.h"
#include "Logger.h"
#include "Menu.h"
#include "UnitTests.h"
using namespace std;

int main() {
    Logger::get().init("socialnetwork.log", LogLevel::DEBUG, true);
    LOG_INFO("Application started");

    runAllTests();
    LOG_DEBUG("Unit tests completed");

    SocialNetwork net;
    LOG_INFO("Created SocialNetwork instance");

    runMenu(net);

    LOG_INFO("Application terminated normally");
    Logger::get().shutdown();
    
    return 0;
}