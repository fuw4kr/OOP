#ifndef BFS_H
#define BFS_H

#include <map>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

class BFS {
protected:
    map<int, vector<int>> adjacencyList;

public:
    BFS() {}

    void buildGraph(const vector<pair<int, int>>& edges) {
        adjacencyList.clear();
        for (auto& edge : edges) {
            adjacencyList[edge.first].push_back(edge.second);
            adjacencyList[edge.second].push_back(edge.first); 
        }
    }

    map<int, int> breadthFirstSearch(int start) {
        map<int, int> dist;
        queue<int> q;
        q.push(start);
        dist[start] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adjacencyList[u]) {
                if (dist.count(v) == 0) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return dist;
    }

    bool isConnected(int start, int totalVertices) {
        auto dist = breadthFirstSearch(start);
        return dist.size() == totalVertices;
    }
};

#endif // BFS_H
 
