#include "SocialNetwork.h"
#include <iostream>
#include <set>
using namespace std;

void SocialNetwork::addUser(User* user) {
    addVertex(user); 
}

void SocialNetwork::removeUser(int userId) {
    removeVertex(userId); 
}

User* SocialNetwork::getUser(int userId) const {
    return dynamic_cast<User*>(getVertex(userId));
}

void SocialNetwork::addFriendship(int userA, int userB) {
    addEdge(new Friendship(userA, userB));
    addEdge(new Friendship(userB, userA));
}

void SocialNetwork::removeFriendship(int userA, int userB) {
    removeEdge(userA, userB);
    removeEdge(userB, userA);
}

void SocialNetwork::addSubscription(int followerId, int followeeId) {
    addEdge(new Subscription(followerId, followeeId));
    User* f = getUser(followerId);
    User* fe = getUser(followeeId);
    if (f) f->addFollowing();
    if (fe) fe->addFollower();
}

void SocialNetwork::sendMessage(int senderId, int receiverId, const string& text) {
    addEdge(new Message(senderId, receiverId, text));
    User* sender = getUser(senderId);
    User* receiver = getUser(receiverId);
    if (sender) sender->sendMessage();
    if (receiver) receiver->receiveMessage();
}

void SocialNetwork::addPost(int authorId, const string& content) {
    addEdge(new Post(authorId, content));
    User* author = getUser(authorId);
    if (author) author->addPost();
}

vector<User*> SocialNetwork::getFriendsOfUser(int userId) {
    vector<User*> friends;
    for (int friendId : getNeighbors(userId)) {
        if (auto* u = dynamic_cast<User*>(getVertex(friendId)))
            friends.push_back(u);
    }
    return friends;
}

vector<User*> SocialNetwork::findMutualFriends(int userA, int userB) {
    auto friendsA = getFriendsOfUser(userA);
    auto friendsB = getFriendsOfUser(userB);
    vector<User*> mutual;
    for (auto* ua : friendsA)
        for (auto* ub : friendsB)
            if (ua->getId() == ub->getId())
                mutual.push_back(ua);
    return mutual;
}

vector<User*> SocialNetwork::findCloseFriends(int userId) {
    set<int> closeSet;
    auto friends = getFriendsOfUser(userId);
    for (auto* f : friends) {
        for (auto* ff : getFriendsOfUser(f->getId())) {
            if (ff->getId() != userId)
                closeSet.insert(ff->getId());
        }
    }
    vector<User*> result;
    for (int id : closeSet)
        if (auto* u = getUser(id))
            result.push_back(u);
    return result;
}

vector<User*> SocialNetwork::findUsersByLocation(const string& location) {
    vector<User*> result;
    for (auto* v : getAllVertices()) { 
        auto* u = dynamic_cast<User*>(v);
        if (u && u->getLocation() == location)
            result.push_back(u);
    }
    return result;
}

vector<User*> SocialNetwork::findCommonSubscriptions(int userA, int userB) {
    set<int> subsA, subsB;
    for (auto* e : getAllEdges()) {
        if (Subscription* s = dynamic_cast<Subscription*>(e)) {
            if (s->getFrom() == userA) subsA.insert(s->getTo());
            if (s->getFrom() == userB) subsB.insert(s->getTo());
        }
    }
    vector<User*> res;
    for (int id : subsA) if (subsB.count(id) && getUser(id)) res.push_back(getUser(id));
    return res;
}

bool SocialNetwork::areConnected(int userA, int userB) {
    return GraphAlgorithms::hasPath(userA, userB);
}

int SocialNetwork::distanceBetween(int userA, int userB) {
    auto dist = GraphAlgorithms::breadthFirstSearch(userA);
    return dist.count(userB) ? dist[userB] : -1;
}

map<int, int> SocialNetwork::shortestPathsFrom(int startId) {
    return GraphAlgorithms::dijkstra(startId);
}

map<int, double> SocialNetwork::userCentrality() {
    return GraphAlgorithms::computeDegreeCentrality();
}

vector<vector<int>> SocialNetwork::detectFriendGroups() {
    return GraphAlgorithms::findTriangles();
}

void SocialNetwork::printNetwork() const {
    cout << "=== USERS ===" << endl;
    for (auto* v : getAllVertices()) {
        v->print();
    }
    cout << "=== FRIENDSHIPS ===" << endl;
    for (auto* e : getAllEdges()) {
        e->print();
    }
}
