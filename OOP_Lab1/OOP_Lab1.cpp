#include "SocialNetwork.h"
#include "Menu.h"
#include "UnitTests.h"
using namespace std;

int main() {
    runAllTests();
    SocialNetwork net;
    runMenu(net);

    return 0;
}