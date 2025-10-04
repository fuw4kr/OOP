#ifndef SOCIALNETWORK_H
#define SOCIALNETWORK_H

#include "Graph.h"
#include "User.h"
#include "BFS.h"
#include <map>
#include <vector>
#include <set>
using namespace std;

class SocialNetwork : public Graph, public BFS {
private:
    map<int, Vertex*> users;
    multimap<int, Edge*> edges;

    vector<pair<int, int>> getEdgePairs() const;

public:
    ~SocialNetwork();

    void addVertex(Vertex* v) override;
    void addEdge(Edge* e) override;
    void removeVertex(int id) override;
    void removeEdge(int from, int to) override;
    Vertex* findUser(int id) const;
    void print() const override;

    bool isConnected();
    int distance(int from, int to);


    vector<User*> findCommonFriends(User* a, User* b);
    vector<User*> findCloseFriends(User* user);
    vector<User*> findCommonSubscriptions(User* a, User* b);
    vector<User*> findUsersWithSameLocation(const  string& location);
};

#endif // SOCIALNETWORK_H
