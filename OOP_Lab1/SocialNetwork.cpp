#include "SocialNetwork.h"
#include <iostream>
#include <fstream>
#include <set>
#include <cstdlib>    
#include <ctime>
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
    vector<pair<int, int>> edgesList;
    for (auto* e : getAllEdges()) {
        edgesList.push_back({ e->getFrom(), e->getTo() });
    }
    buildGraph(edgesList);
    return GraphAlgorithms::hasPath(userA, userB);
}

int SocialNetwork::distanceBetween(int userA, int userB) {
    auto dist = GraphAlgorithms::breadthFirstSearch(userA);
    return dist.count(userB) ? dist[userB] : -1;
}

map<int, int> SocialNetwork::shortestPathsFrom(int startId) {
    vector<pair<int, int>> edgesList;
    for (auto* e : getAllEdges()) {
        edgesList.push_back({ e->getFrom(), e->getTo() });
    }
    buildGraph(edgesList);
    return GraphAlgorithms::dijkstra(startId);
}

map<int, double> SocialNetwork::userCentrality() {
    vector<pair<int, int>> edgesList;
    for (auto* e : getAllEdges()) {
        edgesList.push_back({ e->getFrom(), e->getTo() });
    }
    buildGraph(edgesList);
    return GraphAlgorithms::computeDegreeCentrality();
}

vector<vector<int>> SocialNetwork::detectFriendGroups() {
    vector<pair<int, int>> edgesList;
    for (auto* e : getAllEdges()) {
        edgesList.push_back({ e->getFrom(), e->getTo() });
    }
    buildGraph(edgesList);
    return GraphAlgorithms::findTriangles();
}

void SocialNetwork::generateRandomUsers(int n) {
    srand(static_cast<unsigned>(time(0)));

    vector<string> names = {
        "Alice", "Bob", "Sophia", "Diana", "Eve", "James", "Mia",
        "Robert", "Ivan", "Judy", "Kevin", "Allison", "Liza", "Nina", "Gregory"
    };

    vector<string> locations = {
        "Kyiv", "Lviv", "Odesa", "Kharkiv", "Dnipro", "Vinnytsia", "Poltava"
    };

    for (int i = 0; i < n; ++i) {
        string name = names[rand() % names.size()] + to_string(i + 1);
        string email = name + "@mail.com";
        User* u = new User(i, name, email);
        u->updateLocation(locations[rand() % locations.size()]);
        u->setGender((rand() % 2 == 0) ? "Male" : "Female");
        u->setBirthday("199" + to_string(rand() % 10) + "-0" + to_string(rand() % 9 + 1) + "-1" + to_string(rand() % 9));
        addVertex(u);
    }

    for (int i = 0; i < n * 1.5; ++i) {
        int u1 = rand() % n;
        int u2 = rand() % n;
        int u3 = rand() % n;
        int u4 = rand() % n;
        int u5 = rand() % n;
        int u6 = rand() % n;
        if (u1 != u2) addEdge(new Friendship(u1, u2));
        if (u3 != u4) addEdge(new Subscription(u3, u4));
        addEdge(new Post(rand() % n, "post"));
        if (u5 != u6) addEdge(new Message(u5, u6, "message"));
    }
    cout << "+ " << n << " random users created." << endl;
}

void SocialNetwork::saveToTextFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << filename << " for writing.\n";
        return;
    }

    file << "USERS\n";
    for (auto* v : getAllVertices()) {
        auto* u = dynamic_cast<User*>(v);
        if (u) {
            file << "User ID: " << u->getId()
                << ", Name: " << u->getName()
                << ", Email: " << u->getEmail()
                << ", Bio: " << u->getBio()
                << ", Location: " << u->getLocation()
                << "\n";
        }
    }

    file << "\nRELATIONSHIPS\n";
    for (auto* e : getAllEdges()) {
        if (auto* f = dynamic_cast<Friendship*>(e)) {
            file << "Friendship: " << f->getFrom() << " <-> " << f->getTo() << "\n";
        }
        else if (auto* s = dynamic_cast<Subscription*>(e)) {
            file << "Subscription: " << s->getFrom() << " -> " << s->getTo() << "\n";
        }
        else if (auto* m = dynamic_cast<Message*>(e)) {
            file << "Message: " << m->getFrom() << " -> " << m->getTo()
                << " : " << m->getText() << "\n";
        }
        else if (auto* p = dynamic_cast<Post*>(e)) {
            file << "Post by User " << p->getFrom() << ": " << p->getContent() << "\n";
        }
    }

    file.close();
    cout << "Social network data saved to " << filename << endl;
}

    void SocialNetwork::printNetwork() const {
    cout << "USERS" << endl;
    for (auto* v : getAllVertices()) {
        v->print();
    }
    cout << "FRIENDSHIPS" << endl;
    for (auto* e : getAllEdges()) {
        e->print();
    }
}