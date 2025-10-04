#include "SocialNetwork.h"
#include <iostream>
using namespace std;

vector<pair<int, int>> SocialNetwork::getEdgePairs() const {
    vector<pair<int, int>> pairs;
    for (auto& e : edges) {
        pairs.push_back({ e.second->getFrom(), e.second->getTo() });
    }
    return pairs;
}

SocialNetwork::~SocialNetwork() {
    for (auto& p : users) delete p.second;
    for (auto& e : edges) delete e.second;
}

void SocialNetwork::addVertex(Vertex* v) {
    users[v->getId()] = v;
}

void SocialNetwork::addEdge(Edge* e) {
    edges.insert({ e->getFrom(), e });
}

void SocialNetwork::removeVertex(int id) {
    if (users.count(id)) {
        delete users[id];
        users.erase(id);
        for (auto it = edges.begin(); it != edges.end(); )
            if (it->first == id || it->second->getTo() == id)
                it = edges.erase(it);
            else ++it;
    }
}

void SocialNetwork::removeEdge(int from, int to) {
    for (auto it = edges.begin(); it != edges.end(); )
        if (it->first == from && it->second->getTo() == to) {
            delete it->second;
            it = edges.erase(it);
        }
        else ++it;
}

Vertex* SocialNetwork::findUser(int id) const {
    auto it = users.find(id);
    return (it != users.end()) ? it->second : nullptr;
}

void SocialNetwork::print() const {
    cout << "--- Users ---" << endl;
    for (auto& p : users) p.second->print();
    cout << "--- Connections ---" << endl;
    for (auto& e : edges) e.second->print();
}

bool SocialNetwork::isConnected() {
    if (users.empty()) return true;
    buildGraph(getEdgePairs());
    int startId = users.begin()->first;
    return BFS::isConnected(startId, users.size());
}

int SocialNetwork::distance(int from, int to) {
    if (users.count(from) == 0 || users.count(to) == 0) return -1;
    buildGraph(getEdgePairs());
    auto dist = breadthFirstSearch(from);
    return dist.count(to) ? dist[to] : -1;
}

 vector<User*> SocialNetwork::findCommonFriends(User* a, User* b) {
     vector<User*> common;
    if (!a || !b) return common;

    int aId = a->getId();
    int bId = b->getId();
     set<int> friendsA, friendsB;

    for (auto& e : edges) {
        Friendship* f = dynamic_cast<Friendship*>(e.second);
        if (!f) continue;

        if (f->getFrom() == aId) friendsA.insert(f->getTo());
        else if (f->getTo() == aId) friendsA.insert(f->getFrom());

        if (f->getFrom() == bId) friendsB.insert(f->getTo());
        else if (f->getTo() == bId) friendsB.insert(f->getFrom());
    }

    for (int id : friendsA) {
        if (friendsB.find(id) != friendsB.end()) {
            User* u = dynamic_cast<User*>(findUser(id));
            if (u) common.push_back(u);
        }
    }
    return common;
}

 vector<User*> SocialNetwork::findCloseFriends(User* user) {
     vector<User*> closeFriends;
    if (!user) return closeFriends;

    int uid = user->getId();
     set<int> directFriends, closeFriendsSet;

    for (auto& e : edges) {
        Friendship* f = dynamic_cast<Friendship*>(e.second);
        if (!f) continue;

        if (f->getFrom() == uid) directFriends.insert(f->getTo());
        else if (f->getTo() == uid) directFriends.insert(f->getFrom());
    }

    for (int friendId : directFriends) {
        for (auto& e : edges) {
            Friendship* f = dynamic_cast<Friendship*>(e.second);
            if (!f) continue;

            int otherId = -1;
            if (f->getFrom() == friendId) otherId = f->getTo();
            else if (f->getTo() == friendId) otherId = f->getFrom();

            if (otherId != -1 && otherId != uid && directFriends.find(otherId) == directFriends.end()) {
                closeFriendsSet.insert(otherId);
            }
        }
    }

    for (int id : closeFriendsSet) {
        User* u = dynamic_cast<User*>(findUser(id));
        if (u) closeFriends.push_back(u);
    }

    return closeFriends;
}

 vector<User*> SocialNetwork::findCommonSubscriptions(User* a, User* b) {
     vector<User*> commonSubs;
    if (!a || !b) return commonSubs;

    int aId = a->getId();
    int bId = b->getId();

     set<int> subsA, subsB;

    for (auto& e : edges) {
        Subscription* s = dynamic_cast<Subscription*>(e.second);
        if (!s) continue;

        if (s->getFrom() == aId) subsA.insert(s->getTo());
        if (s->getFrom() == bId) subsB.insert(s->getTo());
    }

    for (int id : subsA) {
        if (subsB.find(id) != subsB.end()) {
            User* u = dynamic_cast<User*>(findUser(id));
            if (u) commonSubs.push_back(u);
        }
    }

    return commonSubs;
}

vector<User*> SocialNetwork::findUsersWithSameLocation(const string& location) {
    vector<User*> nearbyUsers;

    for (auto& p : users) {
        User* u = dynamic_cast<User*>(p.second);
        if (u && !u->getLocation().empty() && u->getLocation() == location) {
            nearbyUsers.push_back(u);
        }
    }

    return nearbyUsers;
}