#ifndef UNITTESTS_H
#define UNITTESTS_H

#include "SocialNetwork.h"
#include <vector>

void test_AddUserSuccessfully();
void test_AddFriendship();
void test_FindMutualFriends();
void test_HandleUserNotFound();
void test_AddSubscriptionAndMessage();

void runAllTests();

#endif // UNITTESTS_H
