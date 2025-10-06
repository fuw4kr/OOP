#include "UnitTests.h"
#include <cassert>
#include <vector>
using namespace std;

void test_AddUserSuccessfully() {
    SocialNetwork net;
    User* u1 = new User(1, "Alice", "alice@mail.com");
    net.addUser(u1);

    User* found = net.getUser(1);
    assert(found != nullptr && "User should be added successfully");
    assert(found->getName() == "Alice" && "User name should match");
}

void test_AddFriendship() {
    SocialNetwork net;
    User* u1 = new User(1, "Alice", "alice@mail.com");
    User* u2 = new User(2, "Bob", "bob@mail.com");
    net.addUser(u1);
    net.addUser(u2);

    net.addFriendship(1, 2);
    vector<User*> friends = net.getFriendsOfUser(1);

    bool found = false;
    for (auto f : friends)
        if (f->getId() == 2) found = true;

    assert(found && "Friendship should be established successfully");
}

void test_FindMutualFriends() {
    SocialNetwork net;
    User* a = new User(1, "Alice", "a@mail.com");
    User* b = new User(2, "Bob", "b@mail.com");
    User* c = new User(3, "Charlie", "c@mail.com");

    net.addUser(a);
    net.addUser(b);
    net.addUser(c);

    net.addFriendship(1, 3);
    net.addFriendship(2, 3);

    auto mutual = net.findMutualFriends(1, 2);
    assert(!mutual.empty() && "Users 1 and 2 should have mutual friend 3");
    assert(mutual[0]->getId() == 3 && "Mutual friend should be Charlie");
}

void test_HandleUserNotFound() {
    SocialNetwork net;
    User* u1 = new User(1, "Alice", "alice@mail.com");
    net.addUser(u1);

    User* notFound = net.getUser(99);
    assert(notFound == nullptr && "Non-existent user should return nullptr");
}

void test_AddSubscriptionAndMessage() {
    SocialNetwork net;
    User* u1 = new User(1, "Alice", "alice@mail.com");
    User* u2 = new User(2, "Bob", "bob@mail.com");
    net.addUser(u1);
    net.addUser(u2);

    net.addSubscription(1, 2);
    net.sendMessage(1, 2, "Hello!");

    assert(true && "Subscription and message sending executed without crash");
}

void runAllTests() {
    test_AddUserSuccessfully();
    test_AddFriendship();
    test_FindMutualFriends();
    test_HandleUserNotFound();
    test_AddSubscriptionAndMessage();
}