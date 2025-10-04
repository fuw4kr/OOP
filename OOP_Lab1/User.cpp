#include "User.h"
#include <iostream>
using namespace std;

User::User(int id, string n, string e)
    : Vertex(id), name(n), email(e), bio(""), location(""), phone(""),
    birthday(""), gender(""), reputation(0), followers(0), following(0),
    postsCount(0), messagesSent(0), messagesReceived(0), lastLogin(time(0)) {
}

void User::updateBio(const string& b) { bio = b; }
void User::setBirthday(const string& bday) { birthday = bday; }
void User::setPhone(const string& ph) { phone = ph; }
void User::setGender(const string& g) { gender = g; }
void User::updateLocation(const string& loc) { location = loc; }

void User::addFollower() { followers++; }
void User::addFollowing() { following++; }
void User::addPost() { postsCount++; }
void User::sendMessage() { messagesSent++; }
void User::receiveMessage() { messagesReceived++; }
void User::changeReputation(int delta) { reputation += delta; }

void User::print() const {
    cout << "User ID=" << id
        << ", Name=" << name
        << ", Email=" << email
        << ", Bio=" << bio
        << ", Birthday=" << birthday
        << ", Phone=" << phone
        << ", Gender=" << gender
        << ", Location=" << location
        << ", Followers=" << followers
        << ", Following=" << following
        << ", Posts=" << postsCount
        << ", MessagesSent=" << messagesSent
        << ", MessagesReceived=" << messagesReceived
        << ", Reputation=" << reputation<< endl;
}

Message::Message(int f, int t, string msg) : Edge(f, t), text(msg) {}
Post::Post(int f, string c) : Edge(f, -1), content(c) {}

void Friendship::print() const { cout << "Friendship: " << from << " <-> " << to << endl; }
void Subscription::print() const { cout << "Subscription: " << from << " -> " << to << endl; }
void Message::print() const { cout << "Message: " << from << " -> " << to << " : " << text << endl; }
void Post::print() const { cout << "Post: " << from << " : " << content << endl; }
