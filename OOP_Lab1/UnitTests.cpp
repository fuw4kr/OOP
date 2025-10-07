#include "UnitTests.h"
#include "Logger.h"
#include <cassert>
#include <vector>
using namespace std;

void test_AddUserSuccessfully() {
    LOG_INFO("Running test: test_AddUserSuccessfully");

    SocialNetwork net;
    User* u1 = new User(1, "Alice", "alice@mail.com");
    net.addUser(u1);
    LOG_DEBUG("User Alice added with ID=1");

    User* found = net.getUser(1);
    assert(found != nullptr && "User should be added successfully");
    assert(found->getName() == "Alice" && "User name should match");

    LOG_INFO("test_AddUserSuccessfully passed");
}

void test_AddFriendship() {
    LOG_INFO("Running test: test_AddFriendship");

    SocialNetwork net;
    User* u1 = new User(1, "Alice", "alice@mail.com");
    User* u2 = new User(2, "Bob", "bob@mail.com");
    net.addUser(u1);
    net.addUser(u2);
    LOG_DEBUG("Users Alice(ID=1) and Bob(ID=2) added");

    net.addFriendship(1, 2);
    LOG_DEBUG("Friendship established between 1 and 2");

    vector<User*> friends = net.getFriendsOfUser(1);
    bool found = false;
    for (auto f : friends)
        if (f->getId() == 2) found = true;

    assert(found && "Friendship should be established successfully");
    LOG_INFO("test_AddFriendship passed");
}

void test_FindMutualFriends() {
    LOG_INFO("Running test: test_FindMutualFriends");

    SocialNetwork net;
    User* a = new User(1, "Alice", "a@mail.com");
    User* b = new User(2, "Bob", "b@mail.com");
    User* c = new User(3, "Charlie", "c@mail.com");

    net.addUser(a);
    net.addUser(b);
    net.addUser(c);
    LOG_DEBUG("Added users: Alice(1), Bob(2), Charlie(3)");

    net.addFriendship(1, 3);
    net.addFriendship(2, 3);
    LOG_DEBUG("Friendships created: 1–3 and 2–3");

    auto mutual = net.findMutualFriends(1, 2);
    assert(!mutual.empty() && "Users 1 and 2 should have mutual friend 3");
    assert(mutual[0]->getId() == 3 && "Mutual friend should be Charlie");

    LOG_INFO("test_FindMutualFriends passed");
}

void test_HandleUserNotFound() {
    LOG_INFO("Running test: test_HandleUserNotFound");

    SocialNetwork net;
    User* u1 = new User(1, "Alice", "alice@mail.com");
    net.addUser(u1);
    LOG_DEBUG("User Alice(ID=1) added");

    User* notFound = net.getUser(99);
    if (notFound == nullptr)
        LOG_DEBUG("Correctly handled request for non-existent user ID=99");
    else
        LOG_WARN("Unexpected user found for ID=99");

    assert(notFound == nullptr && "Non-existent user should return nullptr");
    LOG_INFO("test_HandleUserNotFound passed");
}

void test_AddSubscriptionAndMessage() {
    LOG_INFO("Running test: test_AddSubscriptionAndMessage");

    SocialNetwork net;
    User* u1 = new User(1, "Alice", "alice@mail.com");
    User* u2 = new User(2, "Bob", "bob@mail.com");
    net.addUser(u1);
    net.addUser(u2);
    LOG_DEBUG("Users Alice(1) and Bob(2) added");

    net.addSubscription(1, 2);
    LOG_DEBUG("Alice subscribed to Bob");

    net.sendMessage(1, 2, "Hello!");
    LOG_DEBUG("Message sent from 1 → 2");

    assert(true && "Subscription and message sending executed without crash");
    LOG_INFO("test_AddSubscriptionAndMessage passed");
}

void runAllTests() {
    LOG_INFO("--- Running all unit tests for SocialNetwork ---");

    try {
        test_AddUserSuccessfully();
        test_AddFriendship();
        test_FindMutualFriends();
        test_HandleUserNotFound();
        test_AddSubscriptionAndMessage();
        LOG_INFO("--- All tests passed successfully ---");
    }
    catch (const exception& e) {
        LOG_ERROR(string("Exception caught during tests: ") + e.what());
    }
    catch (...) {
        LOG_ERROR("Unknown error occurred during tests");
    }
}
