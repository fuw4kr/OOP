#include "Graph.h"
#include "GraphAlgorithms.h"  
#include <iostream>
#include <vector>
using namespace std;

Graph::~Graph() {
    for (auto& p : vertices) delete p.second;
    for (auto* e : edges) delete e;
}

void Graph::addVertex(Vertex* v) {
    if (!v) return;
    vertices[v->getId()] = v;
}

void Graph::addEdge(Edge* e) {
    if (!e) return;
    edges.push_back(e);          
}

void Graph::removeVertex(int id) {
    if (vertices.count(id)) {
        auto it = remove_if(edges.begin(), edges.end(), [id](Edge* e) {
            if (e->getFrom() == id || e->getTo() == id) {
                delete e;
                return true;
            }
            return false;
            });
        edges.erase(it, edges.end());

        delete vertices[id];
        vertices.erase(id);
    }
}

void Graph::removeEdge(int from, int to) {
    auto it = remove_if(edges.begin(), edges.end(), [from, to](Edge* e) {
        if (e->getFrom() == from && e->getTo() == to) {
            delete e;
            return true;
        }
        return false;
        });
    edges.erase(it, edges.end());
}


Vertex* Graph::getVertex(int id) const {
    auto it = vertices.find(id);
    return (it != vertices.end()) ? it->second : nullptr;
}

vector<int> Graph::getNeighbors(int id) const {
    vector<int> neighbors;
    for (auto* e : edges) {
        if (e->getFrom() == id) neighbors.push_back(e->getTo());
    }
    return neighbors;
}

vector<Vertex*> Graph::getAllVertices() const {
    vector<Vertex*> result;
    for (auto& p : vertices) result.push_back(p.second);
    return result;
}

vector<Edge*> Graph::getAllEdges() const {
    return edges;
}

void Graph::print() const {
    cout << "Vertices" << endl;
    for (auto& p : vertices) p.second->print();
    cout << "Edges" << endl;
    for (auto* e : edges) e->print();
}
